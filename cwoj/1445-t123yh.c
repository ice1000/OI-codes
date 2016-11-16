#include <iostream>
#include <cstring>

const int maxn = 16;
bool board[maxn][maxn];
char asdf[20];
long long dp[maxn][1 << maxn];

int main() {
	int n, k, i, j, l, cnt;
	long long ans = 0;
	scanf("%i %i", &n, &k);
	memset(board, 0, sizeof(board));
	for (i = 0; i < n; i++) {
		scanf("%s", asdf);
		for (j = 0; j < n; j++)
			board[i][j] = asdf[j] == '#';
	}

	dp[0][0] = 1;
	for (i = 0; i < n; ++i) if (board[0][i]) dp[0][1 << i] = 1;

	for (i = 1; i < n; ++i)
		for (j = 0; j < (1 << n); ++j) {
			for (l = 0; l < n; ++l) {
				if (!(j & (1 << l) && board[i][l])) continue;
				dp[i][j] += dp[i - 1][j & ~(1 << l)];
			}
			dp[i][j] += dp[i - 1][j];
		}
	for (j = 0; j < (1 << n); ++j) {
		cnt = 0;
		for (i = 0; i < n; ++i) if (j & (1 << i)) cnt++;
		if (cnt == k) ans += dp[n - 1][j];
	}
	printf("%lli", ans);
}