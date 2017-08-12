import 'package:test/test.dart';
import 'dart:math';
import 'source.dart';

Random random = new Random(314159265358979);

int getRand(int min, int max) => random.nextInt(max - min) + min;

List<List<int>> shuffle(List<List<int>> o) {
  List<int> x;
  for (int j, i = o.length;
      i > 0;
      j = random.nextInt(i), x = o[--i], o[i] = o[j], o[j] = x);
  return o;
}

main() {
  group("basic cases", () {
    test("0 rectangles", () {
      expect(calculate(const []), equals(0),
          reason: 'calculate([]) should return 0');
    });

    test("1 rectangle", () {
      expect(
          calculate(const [
            const [0, 0, 1, 1]
          ]),
          equals(1),
          reason: 'calculate([[0,0,1,1]]) should return 1');
    });

    test("1 rectangle (version 2)", () {
      expect(
          calculate(const [
            const [0, 4, 11, 6]
          ]),
          equals(22),
          reason: 'calculate([[0, 4, 11, 6]]]) should return 22');
    });

    test("2 rectangles", () {
      expect(
          calculate(const [
            const [0, 0, 1, 1],
            const [1, 1, 2, 2]
          ]),
          equals(2),
          reason: 'calculate([[0,0,1,1], [1,1,2,2]]) should return 2');
    });

    test("2 rectangle (version 2)", () {
      expect(
          calculate(const [
            const [0, 0, 1, 1],
            const [0, 0, 2, 2]
          ]),
          equals(4),
          reason: 'calculate([[0,0,1,1], [0,0,2,2]]) should return 4');
    });

    test("3 rectangle ", () {
      expect(
          calculate(const [
            const [3, 3, 8, 5],
            const [6, 3, 8, 9],
            const [11, 6, 14, 12]
          ]),
          equals(36),
          reason:
              'calculate([[3,3,8,5], [6,3,8,9],[11,6,14,12]]) should return 36');
    });

    test("some rectangles without intersections", () {
      List<List<int>> recs = const [
        const [1, 1, 2, 2],
        const [2, 2, 3, 3],
        const [3, 3, 4, 4],
        const [4, 4, 5, 5],
        const [2, 1, 3, 2]
      ];
      expect(calculate(recs), equals(5), reason: 'should return 5');
    });

    test("some rectangles with simple intersections (version 1)", () {
      List<List<int>> recs = const [
        const [1, 1, 2, 2],
        const [1, 4, 2, 7],
        const [1, 4, 2, 6],
        const [1, 4, 4, 5],
        const [2, 5, 6, 7],
        const [4, 3, 7, 6]
      ];
      expect(calculate(recs), equals(21), reason: 'should return 21');
    });

    test("some rectangles with simple intersections (version 2)", () {
      List<List<int>> recs = const [
        const [1, 3, 4, 5],
        const [2, 1, 4, 7],
        const [3, 4, 5, 6],
        const [6, 6, 8, 7],
        const [5, 3, 8, 4],
        const [6, 0, 7, 3]
      ];
      expect(calculate(recs), equals(24), reason: 'should return 24');
    });

    test("some rectangles with simple intersections (version 2)", () {
      List<List<int>> recs = const [
        const [1, 3, 4, 5],
        const [2, 1, 4, 7],
        const [3, 4, 5, 6],
        const [6, 6, 8, 7],
        const [5, 3, 8, 4],
        const [6, 0, 7, 3]
      ];
      expect(calculate(recs), equals(24), reason: 'should return 24');
    });
  });

  group("difficult cases", () {
    test("rectangles have only common faces", () {
      int stepX = getRand(10, 20),
          stepY = getRand(10, 20),
          startX = getRand(0, 1000),
          startY = getRand(0, 1000),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX + i * stepX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 1, y + 1],
          [x + 1, y, x + 3, y + 2],
          [x, y + 2, x + 3, y + 3],
          [x + 3, y, x + 4, y + 3],
          [x + 2, y + 3, x + 4, y + 5]
        ]));
      }
      expect(calculate(recs), equals(15 * count));
    });

    test("rectangles located far away", () {
      int stepX = getRand(1000, 2000),
          stepY = getRand(1000, 2000),
          startX = getRand(0, 1000),
          startY = getRand(0, 1000),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX + i * stepX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 202, y + 300],
          [x + 100, y + 500, x + 500, y + 765],
          [x + 150, y + 330, x + 170, y + 360]
        ]));
      }
      expect(calculate(recs), equals(167200 * count));
    });

    test("nested rectangles", () {
      int stepX = getRand(10, 200),
          stepY = getRand(10, 200),
          startX = getRand(0, 1000),
          startY = getRand(0, 1000),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX + i * stepX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 1, y + 1],
          [x, y, x + 1, y + 3],
          [x, y + 1, x + 3, y + 2],
          [x, y + 3, x + 4, y + 4],
          [x + 2, y, x + 6, y + 2],
          [x + 3, y + 3, x + 6, y + 5]
        ]));
      }
      expect(calculate(recs), equals(21 * count));
    });

    test("rectangles have a lot of intersections", () {
      int stepX = getRand(10, 200),
          stepY = getRand(10, 200),
          startX = getRand(0, 1000),
          startY = getRand(0, 1000),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX + i * stepX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y + 2, x + 2, y + 4],
          [x + 1, y + 3, x + 3, y + 5],
          [x + 1, y + 1, x + 3, y + 3],
          [x + 7, y + 3, x + 8, y + 4],
          [x + 8, y + 2, x + 9, y + 7],
          [x + 6, y + 2, x + 9, y + 7],
          [x + 3, y + 5, x + 10, y + 6],
          [x + 3, y + 2, x + 6, y + 3],
          [x + 2, y + 4, x + 4, y + 7],
          [x + 9, y, x + 10, y + 3]
        ]));
      }
      expect(calculate(recs), equals(39 * count));
    });

    test("rectangles have long sides", () {
      int stepX = getRand(100000, 111000),
          stepY = getRand(100000, 111000),
          startX = getRand(0, 1000),
          startY = getRand(0, 1000),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX + i * stepX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 30000, y + 1],
          [x, y + 1, x + 1, y + 30001],
          [x + 30000, y + 1, x + 30001, y + 30001]
        ]));
      }
      expect(calculate(recs), equals(90000 * count));
    });

    test("rectangles have only common faces (version 2)", () {
      int stepY = getRand(10, 200),
          startX = getRand(0, 1100),
          startY = getRand(0, 1100),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 1, y + 1],
          [x + 1, y, x + 3, y + 2],
          [x, y + 2, x + 3, y + 3],
          [x + 3, y, x + 4, y + 3],
          [x + 2, y + 3, x + 4, y + 5]
        ]));
      }
      expect(calculate(recs), equals(15 * count));
    });

    test("rectangles located far away (version 2)", () {
      int stepY = getRand(1000, 2000),
          startX = getRand(0, 1100),
          startY = getRand(0, 1100),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 202, y + 300],
          [x + 100, y + 500, x + 500, y + 765],
          [x + 150, y + 330, x + 170, y + 360]
        ]));
      }
      expect(calculate(recs), equals(167200 * count));
    });

    test("nested rectangles (version 2)", () {
      int stepY = getRand(10, 200),
          startX = getRand(0, 1100),
          startY = getRand(0, 1100),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 1, y + 1],
          [x, y, x + 1, y + 3],
          [x, y + 1, x + 3, y + 2],
          [x, y + 3, x + 4, y + 4],
          [x + 2, y, x + 6, y + 2],
          [x + 3, y + 3, x + 6, y + 5]
        ]));
      }
      expect(calculate(recs), equals(21 * count));
    });

    test("rectangles have a lot of intersections (version 2)", () {
      int stepY = getRand(10, 200),
          startX = getRand(0, 1100),
          startY = getRand(0, 1100),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y + 2, x + 2, y + 4],
          [x + 1, y + 3, x + 3, y + 5],
          [x + 1, y + 1, x + 3, y + 3],
          [x + 7, y + 3, x + 8, y + 4],
          [x + 8, y + 2, x + 9, y + 7],
          [x + 6, y + 2, x + 9, y + 7],
          [x + 3, y + 5, x + 10, y + 6],
          [x + 3, y + 2, x + 6, y + 3],
          [x + 2, y + 4, x + 4, y + 7],
          [x + 9, y, x + 10, y + 3]
        ]));
      }
      expect(calculate(recs), equals(39 * count));
    });

    test("rectangles have long sides (version 2)", () {
      int stepY = getRand(100000, 111200),
          startX = getRand(0, 1100),
          startY = getRand(0, 1100),
          count = getRand(1000, 1500);
      List<List<int>> recs = [];
      for (int i = 0; i < count; i++) {
        int x = startX;
        int y = startY + i * stepY;
        recs.addAll(shuffle([
          [x, y, x + 30000, y + 1],
          [x, y + 1, x + 1, y + 30001],
          [x + 30000, y + 1, x + 30001, y + 30001]
        ]));
      }
      expect(calculate(recs), equals(90000 * count));
    });
  });
  group("random tests", () {
    test("some more randomized rectangles", () {
      for (int i = 0; i < 25; i++) {
        int sx = getRand(0, 100000), sy = getRand(0, 100000);
        List<List<int>> recs = new List(getRand(300, 500))
            .map((_) => [
                  sx,
                  sy,
                  sx + getRand(0, 100000),
                  sy + getRand(0, 100000)
                ].toList())
            .toList();
        int expected = calculate(recs);
        int actual = sol(recs);
        expect(actual, equals(expected));
      }
    });
  });
}

class SegForTest implements Comparable<SegForTest> {
  int l, r, h;
  int flag;

  SegForTest(int l, int r, int h, int flag) {
    this.l = l;
    this.r = r;
    this.h = h;
    this.flag = flag;
  }

  @override
  int compareTo(SegForTest seg) => h - seg.h;
}

class SegmentTreeForTest {
  static final MAXN = 15000;
  List<int> cover;
  List<int> sum;
  List<int> x;

  SegmentTreeForTest(int m) {
    cover = new List.filled(MAXN << 2, 0);
    sum = new List.filled(MAXN << 2, 0);
    x = new List();
  }

  int bin(int key, int len, List<int> x) {
    int l = 0, r = len - 1;
    while (l <= r) {
      int m = (l + r) >> 1;
      if (key == x[m])
        return m;
      else if (key < x[m])
        r = m - 1;
      else
        l = m + 1;
    }
    return -1;
  }

  _pushUp(int rt, int l, int r) => sum[rt] = cover[rt] != 0
      ? x[r + 1] - x[l]
      : l == r ? 0 : sum[rt << 1] + sum[rt << 1 | 1];

  void update(int L, int R, int f, int l, int r, int rt) {
    if (L <= l && r <= R) {
      cover[rt] += f;
      _pushUp(rt, l, r);
    } else {
      int m = (l + r) >> 1;
      if (L <= m) update(L, R, f, l, m, rt << 1);
      if (m < R) update(L, R, f, m + 1, r, (rt << 1) | 1);
      _pushUp(rt, l, r);
    }
  }
}

int sol(List<List<int>> rectangles) {
  SegmentTreeForTest tree = new SegmentTreeForTest(rectangles.length << 1);
  List<SegForTest> ss = new List();
  int m = 0;
  rectangles.forEach((List<int> rectangle) {
    int x1 = rectangle[0],
        y1 = rectangle[1],
        x2 = rectangle[2],
        y2 = rectangle[3];
    tree.x.add(x1);
    ss.add(new SegForTest(x1, x2, y1, 1));
    tree.x.add(x2);
    ss.add(new SegForTest(x1, x2, y2, -1));
    m += 2;
  });
  tree.x.sort();
  ss.sort();
  int k = 1;
  for (int i = 1; i < m; i++)
    if (tree.x[i] != tree.x[i - 1]) tree.x[k++] = tree.x[i];
  int ret = 0;
  for (int i = 0; i < m - 1; i++) {
    int l = tree.bin(ss[i].l, k, tree.x);
    int r = tree.bin(ss[i].r, k, tree.x) - 1;
    if (l <= r) tree.update(l, r, ss[i].flag, 0, k - 1, 1);
    ret += tree.sum[1] * (ss[i + 1].h - ss[i].h);
  }
  return ret;
}
