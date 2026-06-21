# TASKS.md

## Current Priorities
### Priority 1 — Hardware calibration path
- verify motor directions by real test
- verify steps/mm with measured motion
- validate line, square, and circle quality

### Completed — Transform logic
- app generation fits G-code into the selected Safe Area
- firmware executes uploaded coordinates directly with transform disabled

### Completed — Segmentation
- firmware uses explicit linear interpolation between stored segment start and target
- long moves remain linear and evenly spaced

### Priority 2 — Unify workspace assumptions
- compare Python defaults vs firmware config
- remove accidental mismatch
- document the chosen workspace clearly

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
