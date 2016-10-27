#include <stdio.h>
#include <stdlib.h>
#include <queue>

#define  SIZE 200
#define  BIG 999999

char map[SIZE][SIZE];
bool mark[SIZE][SIZE];

const int go[4][2] = {
		1, 0,
		0, 1,
		-1, 0,
		0, -1
};

typedef struct point {
	int x, y;
	int step;
	int have;

	point(int x = 0, int y = 0, int step = 0, int have = 0) :
			x(x), y(y), step(step), have(have) { }
} point;

point getFirst(int, int, int);

int main(int argc, char *argv[]) {
	int length = 0;
	int width = 0;
	int chakra = 0;
	int ans = BIG;
	int x, y;
	scanf("%d%d%d\n", &length, &width, &chakra);
	for (int i = 0; i < length; i++) {
		scanf("%s", map[i]);
		getchar();
	}

	std::queue<point> dic = *new std::queue<point>;
	while (!dic.empty()) dic.pop();

	point poi;
	dic.push(getFirst(length, width, chakra));

	while (!dic.empty()) {
		poi = dic.front();
		dic.pop();
		poi.step++;
		for (int i = 0; i < 4; i++) {
			x = poi.x + go[i][0];
			y = poi.y + go[i][1];

			// 判断是否已经到达。
			if (mark[x][y]) break;
			// 判断越界
			if (x >= length or x < 0 or y >= width or y < 0) break;

			switch (map[x][y]) {
				case '*':
					dic.push(*new point(x, y, poi.step, poi.have - 1));
					break;
				case '#':
					if (poi.have) dic.push(*new point(x, y, poi.step, poi.have - 1));
					break;
				case '+':
					if (ans > poi.step) ans = poi.step;
					break;
				default:
					break;
			}
		}
	}

	printf("%d\n", ans == BIG ? -1 : ans);
	return 0;
}

point getFirst(int length, int width, int chakra) {
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
			if (map[i][j] == '@') {
				mark[i][j] = true;
				return *new point(i, j, 0, chakra);
			}
	return point();
}

/*
样例输入1
4 4 1
#@##
**##
###+
****

样例输入2
4 4 2
#@##
**##
###+
****

样例输出1
6

样例输出2
4
 */

