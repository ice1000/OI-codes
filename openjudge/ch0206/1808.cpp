#include <stdio.h>
#include <string.h>
#include <iostream>
#define max(x, y) ((x) > (y) ? (x) : (y))
int dp[202][202], n, m;
char a[202], b[202];
int main(int argc, char *argv[]) {
	int i, j;
	while (std::cin >> a + 1 >> b + 1) {
		n = strlen(a + 1), m = strlen(b + 1);
		memset(dp, 0, 200 * 200);
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= m; ++j) {
				if (a[i] == b[j] and dp[i - 1][j - 1] + 1 > dp[i][j]) dp[i][j] = dp[i - 1][j - 1] + 1;
				else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		printf("%i\n", dp[n][m]);
	}
	return 0;
}
/**
abcfbc         abfcab
programming    contest
abcd           mnp
*/

