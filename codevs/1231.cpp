/*
作者:千里冰封
题目:p1231 最优布线问题
*/

#include <stdio.h>
#include <algorithm>

#define yzh sb
#define size 200005
#define int long long

typedef struct node {
	int val, fr, to;
	const bool operator<(const node& o) const {
		return val < o.val;
	}
	node(int _val = 0, int _fr = 0, int _to = 0) : val(_val), fr(_fr), to(_to) {  }
} node;

int n, uset[size];
node a[size];

int find(int x) {
	return x == uset[x] ? x : (uset[x] = find(uset[x]));
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
	int i, j, x = 0, y, z, w, v, m;
	scanf("%lli %lli", &n, &m);
	z = 0;
	for (i = 0; i <= n; ++i) {
		uset[i] = i;
	}
	for (i = j = 0; i < m; ++i) {
		scanf("%lli %lli %lli", &x, &y, &z);
		a[j++] = *new node(z, x, y);
//		a[j++] = *new node(z, y, z);
	}
//	m <<= 1;
	std::sort(a, a + m);
	z = y = 0;
	for (i = 0; i < m; ++i) {
		w = find(a[i].fr);
		v = find(a[i].to);
		if (w != v) {
			uset[w] = v;
			z += a[i].val;
			if (++y >= n - 1) {
				break;
			}
		}
	}
	printf("%lli", z);
	return 0;
}

/*
3 3
1 2 1
1 3 2
2 3 1
*/


