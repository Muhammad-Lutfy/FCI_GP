# Final Firmware + App G-code Fix Notes

This package applies the two remaining fixes identified after comparing the new mobile app pipeline with the previous Python/Web G-code pipeline.

## 1. Firmware segment interpolation made explicit

Files changed:

- `device_code/firmware/include/gcode_executor.h`
- `device_code/firmware/src/gcode_executor.cpp`

The executor now stores the start point of each long G-code move in:

- `segmentStartX`
- `segmentStartY`

Intermediate segment points are generated with a direct linear interpolation factor:

```cpp
const float t = static_cast<float>(segmentIndex + 1) / static_cast<float>(segmentCount);
outX = segmentStartX + (segmentTargetX - segmentStartX) * t;
outY = segmentStartY + (segmentTargetY - segmentStartY) * t;
```

This makes the motion logic easier to verify and avoids any ambiguity caused by using the robot's continuously changing current position during segmentation.

## 2. App Safe Area fitting now fills the safe rectangle

File changed:

- `app/lib/services/image_to_gcode_converter.dart`

The mobile image-to-G-code converter no longer caps scale at `1.0` during safe-area fitting. Small drawings can now scale up to fill the user's selected safe area while still being clamped inside the safe rectangle.

Old behavior:

```dart
final scale = math.min(settings.safeWidthMm / drawW, settings.safeHeightMm / drawH);
final safeScale = math.min(scale, 1.0);
```

New behavior:

```dart
final safeScale = math.min(settings.safeWidthMm / drawW, settings.safeHeightMm / drawH);
```

## Notes

- The app still generates contour/vector G-code rather than raster scan-line G-code.
- This reduces unnecessary pen up/down operations.
- Safe Area default remains aligned with firmware A4 settings: `X=20`, `Y=20`, `Width=170`, `Height=257`.
- Firmware coordinate transform remains disabled (`scale=1`, `offset=0`) so the ESP32 executes the uploaded app coordinates directly.
