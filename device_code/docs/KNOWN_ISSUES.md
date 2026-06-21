# KNOWN_ISSUES.md

## Confirmed / Suspected Issues

### 1. Double Transform / Double Fit
Status: fixed in current project package

Description:
- App/Python-side generation fits paths into final workspace coordinates.
- Firmware transform is disabled and executes uploaded coordinates directly.

### 2. Segmentation / Interpolation Bug
Status: fixed in current project package

Description:
- Firmware stores the start point of each long move and computes intermediate points with explicit linear interpolation.

### 3. Workspace Mismatch
Status: suspected high-priority issue

Description:
- Python and firmware may not share the same workspace dimensions or paper model

### 4. Motor Direction Ambiguity
Status: unresolved until hardware test

Description:
- sign conventions may be unclear from theory alone

### 5. Legacy Documentation / Stale Files
Status: ongoing risk

Description:
- some files may represent earlier design stages
