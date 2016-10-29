#include <stdio.h>
#include <string.h>
#include <queue>

#ifdef __max
#undef __max
#undef __min
#endif
#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))
#define legal(x, y) \
(((a[x][y]) <= (no.min + mid)) && \
((a[x][y]) >= (no.max - mid)) && \
(!visit[x][y]))

#define add(x, y) \
q.push(*new node(x, y, __min(no.min, a[x][y]), __max(no.max, a[x][y]))), \
++visit[x][y];

int n, a[101][101], visit[101][101];

typedef struct node {
	int x, y, max, min;

	node(int _x = 1, int _y = 1, int _max = a[1][1], int _min = a[1][1]) :
			x(_x), y(_y), max(_max), min(_min) { }
} node;

std::queue<node> q;

int bs(int l, int r) {
	int mid = (l + r) >> 1, x, y, suc = 0;
	printf("<%i|%i|%i>\n", l, mid, r);
	if (l >= r) return r;
	while (!q.empty()) q.pop();
	memset(visit, 0, sizeof(visit));
	q.push(*new node());
	node no;
	while (!q.empty()) {
		no = q.front();
		q.pop();
		x = no.x;
		y = no.y;
		if (x == n && y == n) {
			++suc;
			printf("[%i, %i]\n", no.max, no.min);
			break;
		}
		if (x > 1 && legal(x - 1, y)) add(x - 1, y);
		if (x < n && legal(x + 1, y)) add(x + 1, y);
		if (y > 1 && legal(x, y - 1)) add(x, y - 1);
		if (y < n && legal(x, y + 1)) add(x, y + 1);
	}
	if (suc) return bs(l, mid);
	else return (mid + 1, r);
}

int main(int argc, const char *argv[]) {
//	freopen("C:\\Users\\ice1000\\Desktop\\GDFZOJ\\data\\road\\road8.in", "r", stdin);
	int i, j, max = -1, min = 0xfffff;
	q = *new std::queue<node>;
	scanf("%i", &n);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j) {
			scanf("%i", &a[i][j]);
			if (a[i][j] > max) max = a[i][j];
//			if (a[i][j] < min) min = a[i][j];
		}
	printf("%i", bs(0, max));
	return 0;
}

/*
5
1 1 3 6 8
1 2 2 5 5
4 4 0 3 3
8 0 2 3 4
4 3 0 2 1
*/


