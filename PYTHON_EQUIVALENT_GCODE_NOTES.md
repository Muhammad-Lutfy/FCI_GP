# Python-equivalent Image to G-code update

This version changes the Flutter image converter from raster scan-lines to a contour/vector pipeline that mirrors the original Python project:

```text
Image
→ resize to A4 workspace aspect ratio 210×297
→ grayscale + threshold
→ black-stroke foreground extraction like Python THRESH_BINARY_INV
→ morphology close
→ external contour extraction
→ remove duplicate points
→ Douglas-Peucker simplification
→ nearest-neighbor path ordering
→ fit into user Safe Area
→ G0/G1/M3/M5 G-code
```

## Safe Area

The app now keeps the same firmware coordinate system:

```text
Workspace: 210 × 297 mm
Default Safe Area: X=20, Y=20, W=170, H=257
```

All generated G-code points are clamped inside the user-entered Safe Area.

## Pen up/down reduction

The old raster method produced many short horizontal lines, so it generated many M3/M5 commands. This update draws contours as continuous paths, so each contour normally uses:

```gcode
M5
G0 X.. Y..
M3
G1 X.. Y..
G1 X.. Y..
M5
```

That reduces the number of pen up/down operations and makes the G-code closer to the original Python output.

## UI mapping

The old `rowStepPx` setting is now used as path simplification tolerance:

```text
simplify_tolerance_mm = rowStepPx × 0.4
```

Default rowStepPx=2 means simplify_tolerance=0.8mm, matching the Python default.
