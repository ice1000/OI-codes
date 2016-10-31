#include <stdio.h>
#include <algorithm>

#define size 100001
#define j (i + 1)

typedef struct node {
	int val, to, from;
	const bool operator<(const node& o) const {
	  return val < o.val;
  }
} node;

node a[size];
int uset[size], depth[size], n;

int find(int x) {
	return x == uset[x] ? x : (find(uset[x]));
//	return x == uset[x] ? x : (uset[x] = find(uset[x]));
}

int main(int argc, const char *argv[]) {
	int i, m, x, y, z, w;
	scanf("%i %i", &n, &m);
	for (i = 1; i <= n; ++i) {
		uset[i] = i;
	}
	m <<= 1;
	for (i = 0; i < m; i += 2) {
		scanf("%i %i %i", &a[i].from, &a[i].to, &a[i].val);
		a[j].val = a[i].val;
		a[j].from = a[i].to;
		a[j].to = a[i].from;
	}
	std::sort(a, a + m);
	x = 0;
	y = -1;
	for (i = 0; i < m; ++i) {
		w = find(a[i].from);
    z = find(a[i].to);
		if (w != z) {
			uset[w] = z;
			if (a[i].val > y) {
				y = a[i].val;
			}
			++x;
		}
	}
	printf("%i %i", x, y);
	return 0;
}

/*
4 5
1 2 3
1 4 5
2 4 7
2 3 6
3 4 8
*/

