# TASKS.md

## Current Priorities
### Priority 1 — Verify transform logic
- check whether Python applies final fit transform before G-code export
- check whether firmware applies a second transform
- ensure there is only one final coordinate fitting stage

### Priority 2 — Verify segmentation
- inspect interpolation inside firmware
- ensure intermediate points are evenly spaced
- ensure long moves remain linear and stable

### Priority 3 — Unify workspace assumptions
- compare Python defaults vs firmware config
- remove accidental mismatch
- document the chosen workspace clearly

### Priority 4 — Hardware calibration path
- verify motor directions by real test
- verify steps/mm with measured motion
- validate line, square, and circle quality

## Do Not Do Yet
- do not globally flip all motor direction signs without real hardware validation
- do not rewrite the whole architecture
- do not convert the project to a traditional XY plotter abstraction

## Recommended Test Order
1. straight line
2. square
3. circle
4. simple outline / signature
5. image-to-drawing comparison
