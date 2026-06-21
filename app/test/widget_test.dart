import 'package:flutter_test/flutter_test.dart';
import 'package:spidy_draw/main.dart';

void main() {
  testWidgets('Spidy Draw app starts', (tester) async {
    await tester.pumpWidget(const SpidyDrawApp());
    expect(find.text('Spidy Draw'), findsWidgets);
  });
}
