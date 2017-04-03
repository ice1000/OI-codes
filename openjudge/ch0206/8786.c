#include <stdio.h>
#include <string.h>

#define ms(x, y) memset(x, y, sizeof(x))
#define __max(x, y) ((x) > (y) ? (x) : (y))

int dp[55][55][55][55], a[55][55];

int main(int argc, const char *argv[]) {
	int i, j, k, l, m;
	ms(dp, 0);
	ms(a, 0);
	scanf("%i", &m);
	for (;;) {
		scanf("%i %i %i", &i, &j, &k);
		a[i][j] = k;
		if (!i && !j && !k) break;
	}
	for (i = 1; i <= m; ++i) {
		for (j = 1; j <= m; ++j) {
			for (k = 1; k <= m; ++k) {
				for (l = 1; l <= m; ++l) {
					dp[i][j][k][l] =
					    __max(
					        __max(
					            dp[i - 1][j][k - 1][l],
					            dp[i][j - 1][k][l - 1]),
					        __max(
					            dp[i][j - 1][k - 1][l],
					            dp[i - 1][j][k][l - 1])
					    ) + a[i][j] + a[k][l];
					if (i == k && j == l) {
						dp[i][j][k][l] -= a[i][j];
					}
				}
			}
		}
	}
	printf("%i", dp[m][m][m][m]);
	return 0;
}

