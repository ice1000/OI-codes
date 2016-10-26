/*
作者:千里冰封
题目:p1169 传纸条
*/

#include <stdio.h>
#include <string.h>

#define ms(x, y) memset(x, y, sizeof(x))
#define __max(x, y) ((x) > (y) ? (x) : (y))

int dp[55][55][55][55], a[55][55];

int main(int argc, const char *argv[]) {
	int i, j, k, l, m, n;
	ms(dp, 0);
	ms(a, 0);
	scanf("%i %i", &m, &n);
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {
			scanf("%i", &a[i][j]);
		}
	}
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= n; ++j) {
			for (k = 1; k <= m; ++k) {
				for (l = 1; l <= n; ++l) {
					if ((i != k && j != l) || (i == m && j == n)) {
						dp[i][j][k][l] =
						  __max(
						    __max(
						      dp[i - 1][j][k - 1][l],
						      dp[i][j - 1][k][l - 1]),
						    __max(
						      dp[i][j - 1][k - 1][l],
						      dp[i - 1][j][k][l - 1])
						  ) + a[i][j] + a[k][l];
					}
				}
			}
		}
	}
	printf("%i", dp[m][n][m][n]);
	return 0;
}

/*
3 3
0 3 9
2 8 5
5 7 0
*/

