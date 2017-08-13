import 'dart:math';

import 'package:test/test.dart';

import 'source.dart';

/// The p list is organized by price to foot by index, so the
/// 1st element contains the price for 1 ft, 2nd is for 2 ft,
/// 3rd is 3 ft, etc...

main() {
//         0    1    2    3    4    5    6    7... and so on
  var p = const [
    0, 1, 5, 8, 9, 10, 17, 17, 20, 24, // 0X's
    30, 32, 35, 39, 43, 43, 45, 49, 50, 54, // 1X's
    57, 60, 65, 68, 70, 74, 80, 81, 84, 85, // 2X's
    87, 91, 95, 99, 101, 104, 107, 112, 115, 116, // 3X's
    119, 121, 125, 129, 131, 134, 135, 140, 143, 145, // 4X's
    151
  ]; // 50th element
// Note that the 0th element has a cost of $0

  group("Example Log", () {
    test("The optimal price for n = 0 should be \$0",
        () => expect(cutLog(p, 0), equals(0)));
    test("The optimal price for n = 1 should be \$1",
        () => expect(cutLog(p, 1), equals(1)));
    test("The optimal price for n = 5 should be \$13",
        () => expect(cutLog(p, 5), equals(13)));
    test("The optimal price for n = 8 should be \$22",
        () => expect(cutLog(p, 8), equals(22)));
    test("The optimal price for n = 10 should be \$30",
        () => expect(cutLog(p, 10), equals(30)));
    test("The optimal price for n = 22 should be \$65",
        () => expect(cutLog(p, 22), equals(65)));
    test("The optimal price for n = 23 should be \$69",
        () => expect(cutLog(p, 23), equals(69)));
    test("The optimal price for n = 37 should be \$112",
        () => expect(cutLog(p, 37), equals(112)));
    test("The optimal price for n = 41 should be \$125",
        () => expect(cutLog(p, 41), equals(125)));
    test("The optimal price for n = 50 should be \$153",
        () => expect(cutLog(p, 50), equals(153)));
  });

// Your new function as given to you by me, your boss.
  Function cutLog4Test = (List p, int n) {
    if (n == 0) return 0;
// Some array to store calculated values
    var resultTable = new List(n + 1);
    for (int i = 0; i <= n; i++) resultTable[i] = 0;
// try all lengths up to 'n'
    for (int j = 1; j <= n; j++) {
//try to cut out one piece along the price table
//and calculate the price as sum of this piece plus the price of 'the rest'
      for (int k = 1; k <= j; k++) {
        // Two nested loops = Θ(n^2)
// no magic: since we start at length 0,
// we will already have calculated the price of 'the rest' in our resultTable
        resultTable[j] = max(resultTable[j], p[k] + resultTable[j - k]);
      }
    }
    return resultTable[n]; // Good luck intern!
  };

  group("Random tests", () {
    // I used my face to roll across the keyboard
    // to make this number
    Random r = new Random(2938293728947);
    for (int i = 0; i < 10; i++) {
      List<int> p = new List.filled(50, 0);
      for (int j = 1; j < p.length; j++)
        p[j] = p[j - 1] + (r.nextDouble() * 10 + 1).toInt();
      print("Testing for:\np = $p");
      for (int k = 0; k < 20; k++) {
        int n = (r.nextDouble() * p.length).toInt();
        test("Testing for n = ${n}", () {
          int actual = cutLog(p, n);
          int expected = cutLog4Test(p, n);
          expect(actual, expected);
        });
      }
    }
  });
}

