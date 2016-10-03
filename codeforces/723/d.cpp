#include <stdio.h>
#include <algorithm>

struct LoverFucker {
	int begin, size;

	int end () { return begin + size; }

	bool operator< (const LoverFucker &o) const {
		return size > o.size;
	}
} a[3000];

int n, m, k, poi[3000][2], p_index = 0, a_index, motherFucker;
char map[60][60], mark[60][60];

int dfs (int x, int y) {
	/// 退出dfs
	if (mark[x][y]) return 0;
	if (map[x][y] != '.') return 0;
	/// 记录
	poi[p_index][0] = x;
	poi[p_index++][1] = y;
	/// 标记
	++mark[x][y];
	dfs(x - 1, y);
	dfs(x, y - 1);
	dfs(x + 1, y);
	dfs(x, y + 1);
}

int main (int argc, char *argv[]) {
	int i, j, k;
	scanf("%i %i %i", &n, &m, &k);

	for (i = 0; i < n; ++i)
		scanf("%s", &map[i]);

	/// 沿海地区
	for (i = 0; i < n; ++i) {
		if (map[i][0] == '.') map[i][0] = '#';
		if (map[i][m - 1] == '.') map[i][m - 1] = '#';
	}

	for (i = 0; i < m; ++i) {
		if (map[0][i] == '.') map[0][i] = '#';
		if (map[n - 1][i] == '.') map[n - 1][i] = '#';
	}


	for (i = 1; i < n - 1; ++i)
		for (j = 1; j < m - 1; ++j)
			if (!mark[i][j] && map[i][j] != '*') {
				/// 记录当前水池的起始点和大小
				a[a_index].begin = p_index;
				dfs(i, j);
				a[a_index].size = p_index - a[a_index].begin;
				a_index++;
			}

	std::sort(a, a + a_index);

	for (i = 1; i <= k; ++i) {
		for (j = 0; j < a[i].size; ++j) {
			map[poi[j + a[i].begin][0]][poi[j + a[i].begin][1]] = '*';
//			printf("%i %i\n", poi[j][0], poi[j][1]);
		}
		motherFucker += a[i].size;
	}

	printf("%i\n", motherFucker);

	for (i = 0; i <= n; ++i) {
		for (j = 0; j <= m; ++j) {
			printf("%c", map[i][j] == '#' ? '.' : map[i][j]);
		}
		printf("\n");
	}
	return 0;
}




