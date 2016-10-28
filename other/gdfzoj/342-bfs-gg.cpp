#include <stdio.h>
#include <string.h>
#include <queue>

#define legal(x, y) (((a[x][y]) <= (no.min + mid)) && ((a[x][y]) >= (no.max - mid)) && (!visit[x][y]))
#define add(x, y) (q.push(*new node(x, y)), ++visit[x][y])

int n, a[101][101], visit[101][101];

typedef struct node {
	int x, y, max, min;
	node(int _x = 0, int _y = 0, int _max =  0, int _min = 0xfff) : x(_x), y(_y),
		max(_max), min(_min) { }
} node ;

std::queue<node> q;
int bs(int l, int r) {
	if (l >= r) return r;
	int mid = (l + r) >> 1, x, y, suc = 0;
  printf("|%i|\n", mid);
	while (!q.empty()) q.pop();
	memset(visit, 0, sizeof(visit));
	q.push(*new node());
	node no;
	while (!q.empty()) {
	  no = q.front();
	  q.pop();
	  x = no.x;
	  y = no.y;
	  if (x == n - 1 && y == n - 1) {
	    ++suc;
	    break;
	  }
	  if (x >= 0 && legal(x - 1, y)) add(x - 1, y);
	  if (x <  n && legal(x + 1, y)) add(x + 1, y);
	  if (y >= 0 && legal(x, y - 1)) add(x - 1, y);
	  if (y <  n && legal(x, y + 1)) add(x, y + 1);
  }
  if (suc) return bs(l, mid);
  else return (mid + 1, r);
}

int main(int argc, const char *argv[]) {
	int i, j, max = -1, min = 0xfffff;
	q = *new std::queue<node>;
	scanf("%i", &n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			scanf("%i", &a[i][j]);
			if (a[i][j] > max) max = a[i][j];
			if (a[i][j] < min) min = a[i][j];
		}
	printf("%i", bs(0, max - min));
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
