@echo off
cd /d "%~dp0..\app"
flutter clean
flutter pub get
flutter build apk --release
pause
