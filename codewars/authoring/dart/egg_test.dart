import 'package:test/test.dart';
import 'dart:math';
import 'source.dart';

int heightTester(int n, int m) {
  if (n == 0 || m == 0) return 0;
  if (n > m) n = m;
  int c = 1;
  int b = 1;
  int a = 0;
  while (c <= n) {
    int d = (m + 1 - c) * b ~/ c;
    c++;
    b = d;
    a += d;
  }
  return a;
}

main() {
  test("should work for some basic tests", () {
    expect(height(1, 51), equals(51));
    expect(height(2, 1), equals(1));
    expect(height(4, 17), equals(3213));
    expect(height(16, 19), equals(524096));
    expect(height(23, 19), equals(524287));
  });
  test("should work for some advanced tests", () {
    expect(height(13, 550), equals(60113767426276772744951355));
    expect(height(271, 550), equals(
        1410385042520538326622498273346382708200418583791594039531058458108130216985983794998105636900856496701928202738750818606797013840207721579523618137220278767326000095));
    expect(height(531, 550), equals(
        3685510180489786476798393145496356338786055879312930105836138965083617346086082863365358130056307390177215209990980317284932211552658342317904346433026688858140133147));
  });
  var tester = (int a, int b) => expect(height(a, b), equals(heightTester(a, b)));
  test("should work for some serious tests :)", () {
    tester(311, 10131);
    tester(6511, 11731);
    tester(11111, 12911);
    tester(99999, 13911);
  });
  test("should work for some random tests :)", () {
    Random random = new Random(314159265358979);
    tester(random.nextInt(20000), random.nextInt(20000));
    tester(random.nextInt(20000), random.nextInt(20000));
    tester(random.nextInt(20000), random.nextInt(20000));
  });
}
