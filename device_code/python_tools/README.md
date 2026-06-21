# Spidy-Draw

Spidy-Draw is an ESP32-based cable-driven drawing robot. It converts an uploaded image into drawable paths, generates ESP-compatible G-code on a Python host, and executes that G-code on an ESP32 using four synchronized stepper motors and a pen servo.

This is not a classic rigid XY plotter. The firmware drives a cable/pulley mechanism and computes motor motion from cable-length changes.

## Overview

The project is split into two active runtime sides:

- **Python side:** image processing, path extraction, path cleanup, path ordering, preview data, and G-code generation.
- **ESP32 side:** G-code parsing, command queueing, pen control, motion segmentation, cable kinematics, and motor stepping.

The current default workspace model is A4 paper: `210 x 297 mm`. Python-side G-code generation fits drawings into that workspace. The firmware executes uploaded G-code coordinates directly and uses cable kinematics to convert target points into four motor step plans.

## Features

- Image upload and browser-based processing UI.
- OpenCV-based grayscale, threshold, contour extraction, and cleanup pipeline.
- Presets for logos, signatures, fine art, and outlines.
- Path simplification and near-duplicate point filtering.
- Optional path ordering to reduce pen-up travel.
- ESP-compatible G-code output using `G0`, `G1`, `M3`, and `M5`.
- Local bridge endpoint for uploading generated G-code to the ESP32.
- ESP32 Wi-Fi access point and device web interface.
- G-code upload from file or plain text.
- Servo-based pen up/down control.
- Long-move segmentation on firmware side.
- Four-motor cable-length kinematics with synchronized stepping.

## Architecture Summary

```text
Image
  -> Python image processing
  -> vector-like paths in workspace millimeters
  -> Python G-code generation and fit-to-paper
  -> upload to ESP32
  -> firmware G-code queue
  -> segmented target points
  -> cable-length kinematics
  -> synchronized stepper motion + servo pen control
```

### Python Processing Side

Active files:

- `bridge_server.py` - local HTTP server for the browser UI and API endpoints.
- `web/index.html` - Python-side browser UI for image processing and G-code generation.
- `web_handlers.py` - request handlers for image processing, validation, preview, G-code generation, and ESP upload.
- `image_processor.py` - OpenCV image loading, preprocessing, contour extraction, simplification, and pixel-to-mm mapping.
- `path_optimizer.py` - path cleanup and greedy path ordering.
- `preset_modes.py` - stable processing presets.
- `gcode_exporter.py` - helper exports for G-code, SVG, JSON, and stats.

Responsibilities:

- Load and preprocess images.
- Extract contours and convert them into workspace-coordinate paths.
- Simplify paths and remove redundant points.
- Fit generated G-code into the configured paper workspace.
- Generate commands supported by the ESP32 firmware.
- Upload generated G-code to the ESP32 when requested.

### ESP32 Firmware Side

Active files:

- `src/main.cpp` - firmware entry point; initializes state, motors, servo, Wi-Fi, web server, and executor.
- `src/web_server.cpp` - ESP32 web routes for upload, execution, manual movement, status, servo control, stop, and clear.
- `src/gcode_parser.cpp` - parser for supported G-code commands.
- `src/gcode_executor.cpp` - command queue execution, pen state handling, segmentation, bounds checks, and motion dispatch.
- `src/kinematics.cpp` - cable-length calculations and conversion from target point to motor step plan.
- `src/motor_control.cpp` - synchronized half-step motor execution.
- `src/servo_control.cpp` - pen servo control.
- `include/config.h` - workspace, paper model, motor pins, motor calibration defaults, Wi-Fi settings, and motion constants.

Responsibilities:

- Run the ESP32 access point and device web UI.
- Accept G-code uploads.
- Parse and queue supported commands.
- Execute pen up/down commands.
- Segment long moves for smoother motion.
- Convert target coordinates to cable-length deltas.
- Step four motors in sync.

## End-to-End Workflow

1. Start the Python bridge server.
2. Open the local browser UI.
3. Upload an image.
4. Choose a preset or processing parameters.
5. Process the image into paths.
6. Preview and validate the extracted paths.
7. Generate G-code.
8. Upload the G-code to the ESP32.
9. Execute the queued drawing from the ESP32.
10. Validate output on paper and calibrate hardware as needed.

## Project Structure

```text
.
|-- bridge_server.py          # Local Python HTTP bridge and API
|-- image_processor.py        # Image-to-path processing
|-- path_optimizer.py         # Path cleanup and ordering
|-- preset_modes.py           # Processing presets
|-- web_handlers.py           # Python-side API logic
|-- gcode_exporter.py         # Export helpers
|-- requirements.txt          # Python dependencies
|-- platformio.ini            # ESP32 PlatformIO project config
|-- web/
|   `-- index.html            # Python-side browser UI
|-- include/
|   |-- config.h              # Hardware, workspace, and motion constants
|   |-- gcode_executor.h
|   |-- gcode_parser.h
|   |-- gcode_validator.h
|   |-- kinematics.h
|   |-- motor_control.h
|   |-- robot_state.h
|   |-- servo_control.h
|   `-- web_server.h
|-- src/
|   |-- main.cpp              # ESP32 firmware entry point
|   |-- gcode_executor.cpp
|   |-- gcode_parser.cpp
|   |-- kinematics.cpp
|   |-- motor_control.cpp
|   |-- servo_control.cpp
|   |-- web_server.cpp
|   `-- path_format.h         # Legacy/stale path contract header; not active in firmware build
`-- docs/
    |-- AGENTS.md
    |-- PROJECT_CONTEXT.md
    |-- TASKS.md
    |-- ARCHITECTURE.md
    |-- HARDWARE_MODEL.md
    `-- KNOWN_ISSUES.md
```

## Setup

### Python Side

Requirements:

- Python 3
- OpenCV and NumPy from `requirements.txt`

Install dependencies:

```bash
pip install -r requirements.txt
```

Start the local bridge server:

```bash
python bridge_server.py
```

Open:

```text
http://127.0.0.1:8080
```

The bridge server exposes:

- `GET /` - local processing UI
- `GET /api/presets` - available processing presets
- `POST /api/process-image` - image-to-path processing
- `GET /api/preview` - preview path data
- `GET /api/validate-paths` - path validation summary
- `POST /api/generate-gcode` - G-code generation
- `POST /api/upload-to-esp` - upload generated G-code to an ESP32 URL

### ESP32 Firmware

Requirements:

- PlatformIO
- ESP32 board configured by `platformio.ini`
- Arduino framework
- `madhephaestus/ESP32Servo`

Build firmware:

```bash
pio run
```

Upload firmware:

```bash
pio run --target upload
```

Open serial monitor:

```bash
pio device monitor
```

The firmware starts a Wi-Fi access point using values from `include/config.h`:

```text
SSID: CableRobot_Hotspot
Password: robot123
```

After connecting to the ESP32 access point, use the IP printed in the serial monitor to access the device web interface.

## Firmware Build Flow

1. Configure hardware constants in `include/config.h`.
2. Build with `pio run`.
3. Upload with `pio run --target upload`.
4. Monitor boot logs with `pio device monitor`.
5. Confirm the ESP32 access point starts.
6. Upload G-code through the device UI or through the Python bridge.
7. Execute only after the robot is mechanically safe and calibrated.

## Testing

Local software checks:

```bash
python -m py_compile image_processor.py preset_modes.py web_handlers.py path_optimizer.py bridge_server.py gcode_exporter.py
pio run
```

Recommended hardware validation order:

1. Pen up/down check.
2. Manual movement with pen up.
3. Short straight line.
4. Square.
5. Circle.
6. Simple outline or signature.
7. Full image-to-drawing comparison.

Do not treat a successful firmware build as proof that motor directions, steps/mm, cable tension, or drawing accuracy are correct.

## Limitations

- Motor direction signs are hardware-dependent and must be verified on the physical robot.
- `MOTOR_STEPS_PER_MM` values are starting calibration values, not proven final values.
- Anchor offsets in `include/config.h` are configurable assumptions around the paper.
- The firmware supports a small G-code subset: `G0`, `G1`, `M3`, `M5`; `G21` and `G90` are accepted as no-op setup commands.
- Heavy image processing intentionally runs on the Python/laptop side, not on the ESP32.
- Some files under `docs/` are historical copies and may describe older implementation stages.
- `src/path_format.h` appears to be a legacy path contract header and is not part of the active firmware include path.

## Roadmap

- Add explicit calibration workflow for motor direction, steps/mm, and anchor offsets.
- Add hardware-backed test drawings and expected results.
- Improve generated G-code preview and bounds reporting.
- Add automated tests for segmentation and G-code generation behavior.
- Add clearer device status reporting during long executions.
- Document known-good hardware wiring and pulley configuration after physical validation.

## Documentation

Primary engineering docs:

- `docs/PROJECT_CONTEXT.md`
- `docs/TASKS.md`
- `docs/ARCHITECTURE.md`
- `docs/HARDWARE_MODEL.md`
- `docs/KNOWN_ISSUES.md`

When docs conflict with active code, prefer the active code. The current architecture keeps Python-side processing separate from ESP32-side execution.

## Demo

Demo media is not included yet.

Suggested placeholders:

- Photo of the assembled cable-driven robot.
- Short video of line, square, and circle validation.
- Image-to-drawing comparison from the Python UI through ESP32 execution.

## License

No license file is currently included in this repository. Add a license before distributing or accepting external contributions.
