# Stability Fix v3

This version fixes the runtime error:

- `Cannot hit test a render box with no size`

Changes:

1. Removed `RefreshIndicator` from the dashboard body to avoid gesture/hit-test conflicts on some Android devices. Refresh is still available from the AppBar refresh button.
2. Made `WorkflowStepTile` use a fixed width and removed the unsafe `Spacer` pattern inside horizontally scrollable content.
3. Reduced dashboard rebuilds during manual movement. The app no longer calls `setState()` for every manual move step during long press.
4. Kept the smooth manual movement request queue from the performance build.

Run:

```powershell
cd D:\importent\Spidy-Draw-Final-Organized\app
flutter clean
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force .dart_tool -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force android\.gradle -ErrorAction SilentlyContinue
flutter pub get
flutter run
```
