#include <stdio.h>
#include <string.h>

#define mod 1000000007

char seq[1001];
int dp[1001][1001];

int main(int argc, char *argv[]) {
	int i, j, n;
	scanf("%s", seq + 1);
	n = (int) strlen(seq + 1);
	int ret = 1, tot;
	memset(dp[0], 0, sizeof(dp[0]));
	for (i = 1; i <= n; ++i) {
		if (seq[i] == '?') {
			tot = 0;
			for (j = 1; j <= n; ++j) {
				tot = (tot + dp[i][j - 1]) % mod;
			}
			for (j = 1; j <= n; ++j) {
				dp[i][j] = tot;
			}
		} else if (seq[i] == 'I') {
			for (j = 1; j <= n; ++j) {
				dp[i][j] = ;
			}
		} else { }
	}
	return 0;
}
