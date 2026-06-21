# KNOWN_ISSUES.md

## Confirmed / Suspected Issues

### 1. Double Transform / Double Fit
Status: suspected high-priority issue

Description:
- Python may already transform paths into workspace coordinates
- firmware may transform them again before execution

### 2. Segmentation / Interpolation Bug
Status: suspected high-priority issue

Description:
- firmware may compute intermediate segment points incorrectly

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
