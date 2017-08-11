import java.util.Arrays;

import static java.util.Arrays.sort;

public class RectanglesUnion {
		public static class SegmentTree {
				public static class Seg implements Comparable<Seg> {
						int l, r, h;
						int flag;

						Seg(int l, int r, int h, int flag) {
								this.l = l;
								this.r = r;
								this.h = h;
								this.flag = flag;
						}

						@Override
						public int compareTo(Seg seg) {
								return h - seg.h;
						}
				}

				static final int MAXN = 15000;
				private int[] cover;
				private int[] sum;
				private int[] x;

				SegmentTree() {
						cover = new int[MAXN << 2];
						sum = new int[MAXN << 2];
						x = new int[MAXN << 2];
				}

				int bin(int key, int len, int[] x) {
						int l = 0, r = len - 1;
						while (l <= r) {
								int m = (l + r) >> 1;
								if (key == x[m]) return m;
								else if (key < x[m]) r = m - 1;
								else l = m + 1;
						}
						return -1;
				}

				private void pushUp(int rt, int l, int r) {
						if (cover[rt] != 0) sum[rt] = x[r + 1] - x[l];
						else if (l == r) sum[rt] = 0;
						else sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
				}

				void update(int L, int R, int f, int l, int r, int rt) {
						if (L <= l && r <= R) {
								cover[rt] += f;
								pushUp(rt, l, r);
								return;
						}
						int m = (l + r) >> 1;
						if (L <= m) update(L, R, f, l, m, rt << 1);
						if (m < R) update(L, R, f, m + 1, r, rt << 1 | 1);
						pushUp(rt, l, r);
				}
		}

		public static int calculateSpace(int[][] rectangles) {
				SegmentTree tree = new SegmentTree();
				SegmentTree.Seg[] ss = new SegmentTree.Seg[SegmentTree.MAXN << 2];
				int m = 0;
				for (int[] rectangle : rectangles) {
						int x1 = rectangle[0], y1 = rectangle[1], x2 = rectangle[2], y2 = rectangle[3];
						try {
								tree.x[m] = x1;
						} catch (Exception e) {
								System.out.println(Arrays.deepToString(rectangles));
						}
						ss[m++] = new SegmentTree.Seg(x1, x2, y1, 1);
						tree.x[m] = x2;
						ss[m++] = new SegmentTree.Seg(x1, x2, y2, -1);
				}
				sort(tree.x, 0, m);
				sort(ss, 0, m);
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

}

