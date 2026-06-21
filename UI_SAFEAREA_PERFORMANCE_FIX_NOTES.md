# UI + Safe Area UX Fix Notes

This update improves the mobile app UI/UX without changing the image-to-G-code conversion algorithm or the firmware G-code execution logic.

## What changed

- Safe Area presets now update the text fields immediately.
- Safe Area number fields now clamp to the real A4 workspace limits:
  - X: 0..210 mm
  - Y: 0..297 mm
  - Width: 10..210 mm
  - Height: 10..297 mm
- Added a small A4 visual preview showing the Safe Area rectangle on the paper.
- Added a visible processing banner while the app is analyzing the image and extracting contours.
- Cached G-code preview lines instead of splitting the full G-code text on every rebuild.
- Added a scrollbar to the G-code console preview.
- Added an uploaded state badge after successful upload to ESP.
- Added X+/Y+ labels under the manual movement buttons.
- Added status polling backoff after repeated offline failures.
- Added retry action on the connection screen after failed connection.
- Added zoom/pan support to the G-code path preview.
- Optimized `GcodePathPreview.shouldRepaint` to avoid unnecessary repainting.

## Important

The G-code generation logic was not changed in this update. This is a UI/UX and performance/stability update only.
