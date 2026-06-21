# Spidy Draw - ESP URL Only Flutter App Patch

This package replaces the Flutter mobile app UI so it talks directly to the ESP32 only.

## What changed

- Removed Python server URL from the app UI.
- Connection screen now has one field only: ESP32 URL.
- Added direct ESP API service for:
  - `GET /status`
  - `POST /upload-text`
  - `GET /execute`
  - `GET /stop`
  - `GET /clear`
  - `GET /home`
  - `GET /servo?pos=0|1`
  - `GET /move?angle=...&repeats=...`
- Added status polling every 2 seconds.
- Added safer confirmation before running motors.
- Added cleaner dashboard UI.
- Fixed Android manifest issue:
  - Added INTERNET permission.
  - Kept cleartext HTTP enabled for local ESP URL.
  - Fixed the invalid `android:usesCleartextTraffic="true">>` typo.

## How to install

Copy the files in this ZIP over the same paths in your existing project.

Then run:

```bash
flutter clean
flutter pub get
flutter analyze
flutter run
```

For release APK:

```bash
flutter build apk --release
```

## Important

This app now controls ESP32 directly. Image-to-G-code conversion is not inside the mobile app. Generate G-code elsewhere, then upload the `.gcode`, `.nc`, or `.txt` file from the app.
