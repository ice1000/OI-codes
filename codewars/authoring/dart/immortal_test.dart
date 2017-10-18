import 'dart:math';

import 'package:test/test.dart';

import 'source.dart';

class Test {
  static Random r = new Random(951394653);

  static assertEquals(a, b, [r = ""]) => expect(a, equals(b), reason: r);

  static String randomToken() => r.nextInt(10000).toString();
}

main() {
  Random r = new Random(951394653);
  int passed = 0;
  bool good = true;

  int p = 1e9.toInt();

  /** set true to enable debug */
  bool debug = false;

  int log2(int x) {
    int ans = 0;
    while ((x >>= 1) != 0) ans++;
    return ans;
  }

  int mul(int x, int y, int z) {
    if (z == 2) {
      if ((x & 1) != 0)
        y >>= 1;
      else if ((y & 1) != 0)
        x >>= 1;
      else
        throw new Exception("shit");
    }
    return x % p * (y % p) % p;
  }

  int sumTimes(int first, int n, int k, int t) {
    first -= k;
    if (first < 1) {
      n -= 1 - first;
      first = 1;
    }
    if (n <= 0) return 0;
    return mul(mul(first + first + n - 1, n, 2), t, 1);
  }

  int elderAge_(int n, int m, int k, int newp) {
    if (n == 0 || m == 0) return 0;
    if (k < 0) k = 0;
    if (n < m) {
      int tmp = n;
      n = m;
      m = tmp;
    }
    p = newp;
    if (n == m && (n & -n) == n) return sumTimes(1, n - 1, k, m);
    int N = log2(n),
        M = log2(m);
    int centerWidth = 1 << N,
        centerHeight = 1 << M;
    if (N == M) {
      int rightWidth = n - centerWidth,
          bottomHeight = m - centerHeight;
      int bottomSum = sumTimes(centerHeight, centerWidth, k, bottomHeight);
      return ((sumTimes(centerWidth, centerHeight, k, rightWidth) + bottomSum) %
          p +
          (elderAge_(rightWidth, bottomHeight, k, p) +
              elderAge_(centerWidth, centerHeight, k, p)) %
              p) %
          p;
    } else {
      int leftWidth = 1 << N;
      int leftSum = sumTimes(0, leftWidth, k, m);
      int rightSum = elderAge_(n - leftWidth, m, k - leftWidth, p);
      if (leftWidth > k) {
        rightSum += mul(mul(leftWidth - k, m, 1), n - leftWidth, 1);
        rightSum %= p;
      }
      return (leftSum + rightSum) % p;
    }
  }

  test("examples", () {
    expect(5, equals(elderAge(8, 5, 1, 100)), reason: (""));
    expect(224, equals(elderAge(8, 8, 0, 100007)), reason: (""));
    expect(11925, equals(elderAge(25, 31, 0, 100007)), reason: (""));
    expect(4323, equals(elderAge(5, 45, 3, 1000007)), reason: (""));
    expect(1586, equals(elderAge(31, 39, 7, 2345)), reason: (""));
    expect(808451, equals(elderAge(545, 435, 342, 1000007)), reason: (""));
    // You need to run this test very quickly before attempting the actual tests :)
    expect(
        5456283, equals(elderAge(28827050410, 35165045587, 7109602, 13719506)),
        reason: (""));
  });

  test("the elder is interested", () {
    print(
        '<p><font color=\"green\">100 test cases\\nm,n: 2^5 - 2^10\\nl: 0 - 19\\nt: 2^5 - 2^15</font></p>');
    print("Young man, you should learn a thing or two...\n");
    for (int i = 0; i < 100; i++) {
      int m = (pow(2, r.nextDouble() * 5 + 5)).floor(),
          n = (pow(2, r.nextDouble() * 5 + 5)).floor(),
          l = (r.nextDouble() * 20).floor(),
          t = (pow(2, r.nextDouble() * 10 + 5)).floor();
      int expected = elderAge_(m, n, l, t),
          actual = elderAge(m, n, l, t);
      if (expected != actual) {
        good = false;
        if (debug)
          print(
              "The Elder says: \\n<p><font color=\"yellow\">m=$m, n=$n, l=$n, t=$t</font></p>");
      } else
        passed++;
      expect(expected, equals(actual), reason: (""));
    }
  });
  test("the elder is excited", () {
    print(
        '<p><font color=\"yellow\">300 test cases\\nm,n: 2^8 - 2^20\\nl: 0 - 9999\\nt: 2^10 - 2^20</font></p>');
    print("You're too young and too simple!\n");
    for (int i = 0; i < 100; i++) {
      int m = (pow(2, r.nextDouble() * 12 + 8)).floor(),
          n = (pow(2, r.nextDouble() * 12 + 8)).floor(),
          l = (r.nextDouble() * 10000).floor(),
          t = (pow(2, r.nextDouble() * 10 + 10)).floor();
      int expected = elderAge_(m, n, l, t),
          actual = elderAge(m, n, l, t);
      if (expected != actual) {
        good = false;
        if (debug)
          print(
              "The Elder says: \\n<p><font color=\"yellow\">m=$m, n=$n, l=$n, t=$t</font></p>");
      } else
        passed++;
      expect(expected, equals(actual), reason: (""));
    }
  });
  test("the elder is angry", () {
    print(
        '<p><font color=\"red\">500 test cases\\nm,n: 2^32 - 2^48\\nl: 0 - 9999999\\nt: 2^16 - 2^26</font></p>');
    print("Young man, you should learn a thing or two...\n");
    for (int i = 0; i < 100; i++) {
      int m = (pow(2, r.nextDouble() * 16 + 32)).floor(),
          n = (pow(2, r.nextDouble() * 16 + 32)).floor(),
          l = (r.nextDouble() * 1e7).floor(),
          t = (pow(2, r.nextDouble() * 10 + 16)).floor();
      int expected = elderAge_(m, n, l, t),
          actual = elderAge(m, n, l, t);
      if (expected != actual) {
        good = false;
        if (debug)
          print(
              "The Elder says: \\n<p><font color=\"yellow\">m=$m, n=$n, l=$n, t=$t</font></p>");
      } else
        passed++;
      expect(expected, equals(actual), reason: (""));
    }
  });
}
