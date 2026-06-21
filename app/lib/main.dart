import 'package:flutter/material.dart';

import 'screens/connection_screen.dart';
import 'theme/app_theme.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  runApp(const SpidyDrawApp());
}

class SpidyDrawApp extends StatelessWidget {
  const SpidyDrawApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Spidy Draw',
      debugShowCheckedModeBanner: false,
      theme: AppTheme.dark(),
      builder: (context, child) {
        return Directionality(
          textDirection: TextDirection.rtl,
          child: child ?? const SizedBox.shrink(),
        );
      },
      home: const ConnectionScreen(),
    );
  }
}
