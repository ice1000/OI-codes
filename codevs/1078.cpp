/*
作者:千里冰封
题目:p1078 最小生成树
*/

#include <stdio.h>
#include <algorithm>

#define yzh sb
#define size 100005

typedef struct node {
	int val, fr, to;
	const bool operator<(const node& o) const {
		return val < o.val;
	}
} node;

int n, uset[size];
node a[size];

int find(int x) {
	return x == uset[x] ? x : (find(uset[x]));
}

int main(int argc, const char *argv[]) {
	int i, j, x = 0, y, z, w, v;
	scanf("%i", &n);
	z = 0;
	for (i = 0; i <= n; ++i) {
	  uset[i] = i;
	}
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			scanf("%i", &y);
//			a[i * n + j].fr = i;
//			a[i * n + j].to = j;
//			a[i * n + j].val = y;
			if (i != j) {
				a[z].fr = i;
				a[z].to = j;
				a[z].val = y;
				++z;
			}
		}
	}
	std::sort(a, a + n * n);
	z = y = 0;
	for (i = 0; i < n * n; ++i) {
		w = find(a[i].fr);
		v = find(a[i].to);
		if (w ^ v) {
			uset[w] = v;
			z += a[i].val;
			if (++y >= n - 1) {
				break;
			}
		}
	}
	printf("%i", z);
	return 0;
}

/*
4
0 4 9 21
4 0 8 17
9 8 0 16
21 17 16 0
*/


