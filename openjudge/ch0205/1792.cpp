#include <stdio.h>
#include <string.h>
#include <queue>

const int SIZE = 1005;

int step[4][2] = {
		{-1, 0},
		{1,  0},
		{0,  -1},
		{0,  1}
};

typedef struct node {
	int x, y;

	node(int _x = 0, int _y = 0) : x(_x), y(_y) { }
} node;

char a[SIZE][SIZE];
std::queue<node> q;

int main(int argc, const char *argv[]) {
	int t, i, i1;
	q = *new std::queue<node>;
	memset(a, 0, sizeof(a));
	scanf("%i", &t);
	while (t--) {
		i1 = 1;
		int hx, lx, hy, ly, cnt;
		scanf("%i", &cnt);
		for (i = 0; i < cnt; i++)
			scanf("%s", a[i]);
		scanf("%i %i %i %i", &lx, &ly, &hx, &hy);
		while (!q.empty())q.pop();
		node now;
		q.push(*new node(hx, hy));
		if (hx == lx and hy == ly) {
			printf("YES\n");
			continue;
		}
		if (a[hx][hy] == '#' or a[lx][ly] == '#') {
			printf("NO\n");
			continue;
		}
		int x;
		int y;
		while (!q.empty()) {
			now = q.front(), q.pop();
			a[now.x][now.y] = '#';
			for (i = 0; i < 4; i++) {
				x = now.x + step[i][0];
				y = now.y + step[i][1];
				if (x >= 0 and
				    y >= 0 and
				    x < cnt and
				    y < cnt and
				    a[x][y] == '.') {
					a[x][y] = '#';
					if (x == lx && y == ly) {
						printf("YES\n"), i1 = 0;
						break;
					}
					q.push(*new node(x, y));
				}
			}
		}
		if (i1) printf("NO\n");
	}
	return 0;
}

/*
3
3
.##
..#
#..
0 0 2 2
5
.....
###.#
..#..
###..
...#.
0 0 4 0
1
.
0 0 0 0
*/

