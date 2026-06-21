import 'package:flutter/material.dart';

import '../theme/app_theme.dart';

class AppBackground extends StatelessWidget {
  const AppBackground({super.key, required this.child});

  final Widget child;

  @override
  Widget build(BuildContext context) {
    return Container(
      decoration: const BoxDecoration(gradient: AppTheme.appBackground),
      child: Stack(
        children: [
          const Positioned(
            top: -120,
            right: -90,
            child: _GlowOrb(size: 260, color: AppTheme.primary),
          ),
          const Positioned(
            top: 150,
            left: -120,
            child: _GlowOrb(size: 240, color: AppTheme.purple),
          ),
          const Positioned(
            bottom: -120,
            right: 30,
            child: _GlowOrb(size: 230, color: AppTheme.secondary),
          ),
          Positioned.fill(child: child),
        ],
      ),
    );
  }
}

class _GlowOrb extends StatelessWidget {
  const _GlowOrb({required this.size, required this.color});

  final double size;
  final Color color;

  @override
  Widget build(BuildContext context) {
    return IgnorePointer(
      child: Container(
        width: size,
        height: size,
        decoration: BoxDecoration(
          shape: BoxShape.circle,
          gradient: RadialGradient(
            colors: [
              color.withValues(alpha: 0.22),
              color.withValues(alpha: 0.06),
              Colors.transparent,
            ],
          ),
        ),
      ),
    );
  }
}
