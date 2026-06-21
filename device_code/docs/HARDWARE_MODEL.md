# HARDWARE_MODEL.md

## Hardware Summary
Spidy-Draw is built around an ESP32-controlled cable-driven motion system.

The hardware model includes:
- 4 stepper motors
- 1 servo motor
- cable / pulley based motion
- pen holder / pen up-down mechanism
- ESP32 microcontroller
- power system
- fixed drawing surface / paper

## Hardware Roles
### ESP32
- firmware execution
- queue handling
- device-side web communication
- coordinating motion execution
- controlling servo state

### Stepper Motors
- executing synchronized cable-driven movement
- contributing to target position changes through motion logic

### Servo
- pen up
- pen down

## Mechanical Interpretation Rules
- this project must be treated as **cable-driven**
- it must not be silently treated as a rigid XY gantry
- motion comes from cable / geometry relationships
- the code must preserve that logic

## Practical Validation Procedure
Run:
1. line
2. square
3. circle

If the line is wrong:
- inspect transform logic
- inspect motor directions
- inspect steps/mm
- inspect segmentation
