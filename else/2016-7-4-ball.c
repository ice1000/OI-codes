#include <stdio.h>

int n, m, dp[50][50];

void init() {
	freopen("ball.in", "r", stdin);
	freopen("ball.out", "w+", stdout);
}

int main(int argc, char *argv[]) {
	init();
	int i, j;
	scanf("%d%d", &n, &m);
	dp[0][1] = 1;
	for(i = 1; i <= m; i++) {
		for(j = 1; j <= n; j++) {
			int a, b;
			a = j == n ? dp[i - 1][1] : dp[i - 1][j + 1];
			b = j == 1 ? dp[i - 1][n] : dp[i - 1][j - 1];
			dp[i][j] = a + b;
		}
	}
	printf("%d", dp[m][1]);
	return 0;
}
