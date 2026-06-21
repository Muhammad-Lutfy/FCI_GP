# ARCHITECTURE.md

## Overview
Spidy-Draw is organized as a layered system with a strong separation between processing and execution.

The practical pipeline is:
**Image → Paths → G-code → Queue → Motion Execution**

## Layer 1 — Image Processing Layer
Runs on Python side.

Responsibilities:
- load image files
- preprocess image
- detect contours
- simplify contours into paths
- remove duplicate / near-duplicate points
- calculate path metadata
- serialize results for preview and G-code generation

## Layer 2 — G-code Generation Layer
Runs on Python side.

Responsibilities:
- validate processed paths
- transform paths into workspace coordinates
- apply safe margins
- generate G-code commands
- provide preview / stats / debug exports

## Layer 3 — Firmware Parsing / Execution Layer
Runs on ESP32.

Responsibilities:
- parse G-code
- prepare queue
- apply transform / fit logic if used
- manage execution state machine
- trigger pen actions
- prepare movement segments
- call kinematics and motor control

## Layer 4 — Motion / Hardware Control Layer
Low-level execution layer.

Responsibilities:
- compute kinematics
- convert motion targets into motor steps
- synchronize motor stepping
- drive pen servo
- maintain robot state

## Design Principle
Keep heavy processing off the ESP32:
- image processing stays on Python / laptop / browser side
- ESP32 focuses on parsing and motion execution
