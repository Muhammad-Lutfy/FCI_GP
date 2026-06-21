# PROJECT_CONTEXT.md

## Project Summary
Spidy-Draw is a portable cable-driven drawing robot based on **ESP32**.

The full workflow is:
1. image is uploaded
2. image is converted into vector-like paths
3. paths are cleaned, simplified, and optionally reordered
4. validated G-code is generated
5. G-code is uploaded to the ESP32
6. ESP32 executes the drawing using synchronized motion control

This project is best understood as an end-to-end:
**image → paths → validated G-code → drawing execution**
pipeline.

## High-Level Architecture

### Python / Laptop / Browser Side
Responsible for:
- image loading
- preprocessing
- contour extraction
- path simplification
- point cleanup
- path ordering
- G-code generation
- upload bridge / local UI support

Main files:
- `image_processor.py`
- `path_optimizer.py`
- `web_handlers.py`
- `gcode_exporter.py`
- `bridge_server.py`
- `preset_modes.py`

### ESP32 / Firmware Side
Responsible for:
- G-code parsing
- queue preparation
- transform application
- kinematics
- synchronized motor stepping
- servo pen control
- robot state tracking
- device-side web endpoints

Main files:
- `src/gcode_executor.cpp`
- `src/gcode_parser.cpp`
- `src/kinematics.cpp`
- `src/motor_control.cpp`
- `src/servo_control.cpp`
- `src/web_server.cpp`
- `src/main.cpp`

## Mechanical Understanding
- the project is **cable-driven**
- it is **not** a classic XY gantry plotter
- ESP32 executes motion, not heavy image processing
- Python is responsible for image-to-G-code pipeline

## Known Critical Risks
1. possible double transform / double fit
2. possible segmentation interpolation issue
3. possible workspace mismatch
4. motor direction signs must be verified experimentally
5. some files may reflect older project stages

## Stable Conclusions
- the project is split between processing side and execution side
- the project is cable-driven
- ESP32 executes motion
- Python generates and prepares G-code
- transform logic, segmentation, workspace consistency, and hardware calibration are the main technical concerns

## Rules for Future Contributors / Agents
- do not assume XY plotter geometry
- do not assume every doc is current
- do not change workspace defaults without checking both Python and firmware
- keep public README simpler than engineering context, but never let README contradict the real project
