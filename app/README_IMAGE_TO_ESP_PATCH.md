# Spidy Draw - Image to G-code to ESP Flutter App Patch

This package upgrades the ESP-only Flutter app so the phone can:

1. Connect to one ESP32 URL only.
2. Pick an image from gallery or take a photo.
3. Convert the image locally inside Flutter to simple raster G-code.
4. Preview the generated drawing path.
5. Upload the G-code directly to the ESP32.
6. Run / stop / clear / home / move / pen up/down from the app.

## Important behavior

The conversion is local and does **not** use Python/OpenCV. It is intentionally simple and safe for mobile:

- Converts image to black/white using a Threshold slider.
- Generates horizontal drawing strokes from black pixel runs.
- Limits generated commands to 5500 by default to stay below the ESP queue limit.
- Uses `M5`, `G0`, `M3`, `G1`, `M5` for each drawn segment.

This is best for logos, icons, signatures, and simple high-contrast images. Complex photos should be simplified first or tuned with the app sliders.

## Files changed/added

Replace these files in your existing project:

- `pubspec.yaml`
- `android/app/src/main/AndroidManifest.xml`
- `lib/core/app_constants.dart`
- `lib/screens/dashboard_screen.dart`

Add these new files:

- `lib/models/generated_gcode.dart`
- `lib/services/image_to_gcode_converter.dart`
- `lib/widgets/gcode_path_preview.dart`

Existing ESP service files remain compatible with:

- `GET /status`
- `POST /upload-text`
- `GET /execute`
- `GET /stop`
- `GET /clear`
- `GET /home`
- `GET /servo?pos=0|1`
- `GET /move?angle=...&repeats=...`

## How to install

Copy the files in this ZIP over the same paths in your existing Flutter project.

Then run:

```bash
flutter clean
flutter pub get
flutter analyze
flutter run
```

For APK:

```bash
flutter build apk --release
```

## Recommended first test

1. Connect phone to ESP Wi-Fi.
2. Open app and connect to `http://192.168.4.1`.
3. Choose a simple black logo image.
4. Press `تحويل فقط`.
5. Check preview.
6. Press `رفع فقط` first.
7. Then press `تشغيل الموجود` after confirming the robot is safe.

If the preview is too full/black, reduce Threshold or turn off Invert. If it is too empty, increase Threshold or turn on Invert.
