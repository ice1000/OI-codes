/*
作者:千里冰封
题目:p1077 多源最短路
*/

#include <stdio.h>

int a[105][105];

int main (int argc, char *argv[]) {
	int n, i, j, k;
	scanf("%i", &n);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			scanf("%i", &a[i][j]);
	for (k = 1; k <= n; ++k)
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j)
				if (a[i][k] + a[k][j] < a[i][j]) a[i][j] = a[i][k] + a[k][j];
	scanf("%i", &n);
	while (n--) {
		scanf("%i %i", &i, &j);
		printf("%i\n", a[i][j]);
	}
	return 0;
}
