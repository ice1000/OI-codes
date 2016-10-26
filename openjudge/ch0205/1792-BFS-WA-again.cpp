#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

const int SIZE = 1005;

int step[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

typedef struct {
	int x, y;
} node;

char a[SIZE][SIZE];
std::queue<node> q;
int main(int argc, const char *argv[]) {
	int total, counter = 0, i, shitshit;
	scanf("%d", &total);
	while (total--) {
		shitshit = 1;
		int hx, lx, hy, ly, cnt;
		scanf("%d",&cnt);
		for(i = 0; i < cnt; i++)
			scanf("%s",a[i]);
		scanf("%d %d %d %d", &hx, &hy, &lx, &ly);
		while(!q.empty())q.pop();
		node now;
		now.x = hx;
		now.y = hy;
		q.push(now);
		while(!q.empty()) {
			now = q.front(), q.pop();
			if(now.x == lx && now.y == ly) {
				printf("YES\n"), shitshit = 0;
				break;
			}
			a[now.x][now.y] = '#';
			node next;
			for(i = 0; i < 4; i++) {
				int x = now.x + step[i][0];
				int y = now.y + step[i][1];
				if(x >= 0 &&
				        y >= 0 &&
				        x < cnt &&
				        y < cnt &&
				        a[x][y] == '.') {
					a[x][y] = '#';
					next.x = x;
					next.y = y;
					q.push(next);
				}
			}
		}
		if (shitshit) printf("NO\n");
	}
	// system("PAUSE");
	return 0;
}

/*
2
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
*/

