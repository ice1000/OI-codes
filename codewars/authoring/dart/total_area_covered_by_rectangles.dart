class Seg implements Comparable<Seg> {
  int l, r, h;
  int flag;

  Seg(int l, int r, int h, int flag) {
    this.l = l;
    this.r = r;
    this.h = h;
    this.flag = flag;
  }

  @override
  int compareTo(Seg seg) => h - seg.h;
}

class SegmentTree {
  static final MAXN = 15000;
  List<int> cover;
  List<int> sum;
  List<int> x;

  SegmentTree(int m) {
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

int calculate(List<List<int>> rectangles) {
  SegmentTree tree = new SegmentTree(rectangles.length << 1);
  List<Seg> ss = new List();
  int m = 0;
  rectangles.forEach((List<int> rectangle) {
    int x1 = rectangle[0],
        y1 = rectangle[1],
        x2 = rectangle[2],
        y2 = rectangle[3];
    tree.x.add(x1);
    ss.add(new Seg(x1, x2, y1, 1));
    tree.x.add(x2);
    ss.add(new Seg(x1, x2, y2, -1));
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

main() {
  print(calculate(const [
    const [0, 4, 11, 6]
  ]));
}
