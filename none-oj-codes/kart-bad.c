#include <stdio.h>
#include <stdlib.h>

#define int long long

int map[1001][1001];
int origin[1001][1001];
int canBeLoosed[10001], canBeLoosed_Index;

//int cmp(const void *a, const void *b) {
//	return *(int *)a - *(int *)b;
//}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
  freopen("kart.in", "r", stdin);
  freopen("kart.out", "w", stdout);
	int i, j, k, l, m, n, a, b, c, x = 0, y = 0, z;
//	canBeLoosed[canBeLoosed_Index++] = 5;
//	canBeLoosed[canBeLoosed_Index++] = 8;
//	canBeLoosed[canBeLoosed_Index++] = 3;
//	qsort(canBeLoosed, canBeLoosed_Index, sizeof(canBeLoosed[0]), cmp);
//	printf("%i %i %i\n", canBeLoosed[0], canBeLoosed[1], canBeLoosed[2]);
	scanf("%lli %lli", &n, &m);
	for (i = 0; i < m; ++i) {
		scanf("%lli %lli %lli", &a, &b, &c);
//		origin[a][b] = c;
//		origin[b][a] = c;
		map[a][b] = c;
		map[b][a] = c;
		y += c << 1;
	}
	for (k = 1; k <= n; ++k)
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j) {
				if (map[i][j] && map[i][k] && map[k][j]) {
					if (map[i][j] > map[i][k] + map[k][j]) {
						canBeLoosed[canBeLoosed_Index++] = map[i][j];
						x += map[i][j];
						map[i][j] = map[i][k] + map[k][j];
					}
				}
			}
	printf("%lli %lli", (y - x) >> 2, (y - x) >> 2);
	//
	return 0;
}

/*
3 3 1 2 1 1 3 2 2 3 3
*/

