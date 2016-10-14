#include <stdio.h>

char map[1005][1005];

int main(int argc, char *argv[]) {
	freopen("mine.in", "r", stdin);
	freopen("mine.out", "w", stdout);
	int i, j, n, m, l;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i)
		scanf("%s", map[i] + 1);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			if (map[i][j] == '.') {
				l = 0;
				if (map[i + 1][j + 1] == '*') ++l;
				if (map[i + 1][j - 1] == '*') ++l;
				if (map[i - 1][j + 1] == '*') ++l;
				if (map[i - 1][j - 1] == '*') ++l;
				if (map[i + 1][j] == '*') ++l;
				if (map[i - 1][j] == '*') ++l;
				if (map[i][j - 1] == '*') ++l;
				if (map[i][j + 1] == '*') ++l;
				printf("%d ", l);
			} else printf("* ");
		}
		printf("\n");
	}
	return 0;
}
/*
3 3
*.*
...
*.*
*/
