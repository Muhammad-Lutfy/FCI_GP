# Spidy Draw Performance Fix

This build focuses on making manual robot control smoother on real Android phones.

## What changed

- Manual movement no longer uses the global loading lock.
- Arrow buttons stay responsive while ESP32 is replying.
- Only one `/move` HTTP request is sent at a time; rapid taps keep the latest direction only.
- Long press on any arrow now sends repeated movement commands for smoother calibration.
- Status polling is paused during manual movement to avoid fighting the movement requests.
- Status UI no longer rebuilds every poll when nothing changed.
- G-code preview is isolated with `RepaintBoundary` to reduce expensive repaints.
- Manual movement timeout reduced to 2 seconds.
- Status polling interval increased from 2 seconds to 4 seconds.

## How to use

- Tap arrow once = one movement step.
- Hold arrow = continuous smooth movement.
- Release arrow = app refreshes robot status automatically.
