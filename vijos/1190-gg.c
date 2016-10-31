#include <stdio.h>
#include <stdlib.h>

#define size 100001
#define bool int
#define true 1
#define false 0
#define j (i + 1)

typedef struct node {
	int val, to, from;
} node;

node a[size];
int uset[size], depth[size], n;

int cmp(const void *x, const void *y) {
	return ((node *)x)->val > ((node *)y)->val;
}

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
	qsort(a, m, sizeof(node), cmp);
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
//		if (x >= n - 1) {
//			break;
//		}
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

