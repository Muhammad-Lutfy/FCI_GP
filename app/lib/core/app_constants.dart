class AppConstants {
  AppConstants._();

  static const String appName = 'Spidy Draw';
  static const String defaultEspUrl = 'http://192.168.4.1';
  static const String savedEspUrlKey = 'saved_esp_url';

  static const int statusPollSeconds = 4;
  static const int shortTimeoutSeconds = 5;
  static const int manualTimeoutSeconds = 2;
  static const int longTimeoutSeconds = 25;
  static const int maxPreviewLines = 700;

  // Default safe drawing area in millimeters. The user can edit these values
  // from the app before generating G-code.
  static const double defaultSafeXmm = 20;
  static const double defaultSafeYmm = 20;
  static const double defaultSafeWidthMm = 160;
  static const double defaultSafeHeightMm = 110;

  static const int defaultRasterWidthPx = 180;
  static const int defaultThreshold = 145;
  static const int defaultRowStepPx = 2;
  static const int defaultMinRunPx = 2;
  static const int defaultMaxGeneratedCommands = 5500;
}
