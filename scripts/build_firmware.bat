@echo off
cd /d "%~dp0..\device_code\firmware"
pio run
pause
