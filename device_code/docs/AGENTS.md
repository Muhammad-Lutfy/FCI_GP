# AGENTS.md

## Project Identity
This repository is for **Spidy-Draw**, a portable **ESP32 cable-driven drawing robot**.

The system converts:
**image → paths → G-code → ESP32 execution**

This is not a traditional rigid XY plotter project.

## Required Reading Order
Before making any change, read these files in this order:

1. `PROJECT_CONTEXT.md`
2. `TASKS.md`
3. `README.md`
4. `docs/ARCHITECTURE.md`
5. `docs/HARDWARE_MODEL.md`
6. `docs/KNOWN_ISSUES.md`
7. `TECHNICAL_DOCUMENTATION.md` if present

If there is any conflict:
- `PROJECT_CONTEXT.md` is the main engineering source of truth
- `TASKS.md` defines current priorities
- the actual source code wins over outdated docs
- public README may be simplified and should not override engineering reality

## Core Reality of This Project
Important facts that must not be forgotten:

- This project is **cable-driven**
- It is **not** a classic XY gantry / frame plotter
- The **image-processing side** runs on Python / laptop / browser side
- The **motion-execution side** runs on ESP32 firmware side
- The robot uses:
  - 4 stepper motors
  - 1 servo for pen up/down
  - cable-length based motion logic
  - G-code execution through firmware queue
- Any refactor that silently turns the project into a traditional XY plotter is wrong

## Safe Change Policy
When editing this repository:

- prefer minimal, explicit patches
- explain the reason for each motion-related change
- do not blindly change motor direction signs without a real hardware test
- do not invent geometry values that are not justified by code or docs
- do not silently change workspace units or paper model
- do not duplicate transforms between Python-side generation and firmware-side execution
- do not move heavy image processing onto ESP32 unless explicitly requested

## Current High-Risk Areas
These are the most important technical risks already identified:

1. **Possible double transform / double fit**
2. **Segmentation / interpolation bug**
3. **Workspace mismatch**
4. **Motor direction uncertainty**
5. **Legacy / stale documentation**

## Files That Matter Most

### Python / Processing Side
- `image_processor.py`
- `path_optimizer.py`
- `web_handlers.py`
- `gcode_exporter.py`
- `bridge_server.py`
- `preset_modes.py`

### Firmware / ESP32 Side
- `include/config.h`
- `include/gcode_executor.h`
- `include/gcode_parser.h`
- `include/gcode_validator.h`
- `include/kinematics.h`
- `include/motor_control.h`
- `include/servo_control.h`
- `include/robot_state.h`
- `src/gcode_executor.cpp`
- `src/gcode_parser.cpp`
- `src/kinematics.cpp`
- `src/motor_control.cpp`
- `src/servo_control.cpp`
- `src/web_server.cpp`
- `src/main.cpp`

## Validation Expectations
After making changes:
- run Python-side syntax and logic checks if possible
- run tests if available
- report exactly what was verified and what was not
- distinguish between static reasoning, local tests, and real hardware verification

Never claim a hardware fix is confirmed unless it was tested on the actual device.
