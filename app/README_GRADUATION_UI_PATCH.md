# Spidy Draw — Graduation UI Patch

This patch upgrades the Flutter mobile app UI for a graduation project presentation while keeping the same ESP32-only architecture.

## What changed

- Redesigned connection screen with a professional hero panel.
- One ESP32 URL only. No Python server URL is required.
- New graduation dashboard header: `Image → Safe Area → G-code → ESP32`.
- Live robot status card with progress, pen, X/Y, and connection state.
- Demo workflow card showing the full project pipeline step by step.
- Polished Image-to-G-code studio with preview and conversion settings.
- Safe Drawing Area is still user-editable: Start X, Start Y, Safe Width, Safe Height.
- New professional G-code path preview with grid, glow lines, and Safe Area label.
- Cleaner cards, buttons, status pills, gradients, and app background.
- Manual calibration pad redesigned for demo/presentation.

## Replace these files/folders

Copy the included files over your project with the same paths.

Important updated files:

```text
pubspec.yaml
lib/theme/app_theme.dart
lib/screens/connection_screen.dart
lib/screens/dashboard_screen.dart
lib/widgets/app_background.dart
lib/widgets/section_card.dart
lib/widgets/info_tile.dart
lib/widgets/workflow_step.dart
lib/widgets/primary_button.dart
lib/widgets/status_pill.dart
lib/widgets/gcode_path_preview.dart
```

## Run

```bash
flutter clean
flutter pub get
flutter analyze
flutter run
```

## Build APK

```bash
flutter build apk --release
```

## Notes

This is a UI/UX patch. It does not remove image-to-G-code, safe area, or ESP upload/run features from the previous patch.
