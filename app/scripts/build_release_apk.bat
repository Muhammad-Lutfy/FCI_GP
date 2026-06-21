@echo off
flutter clean
flutter pub get
flutter analyze
flutter build apk --release
pause
