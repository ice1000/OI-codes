#include <stdio.h>

void init() {
	freopen("desert.in", "r", stdin);
	freopen("desert.out", "w+", stdout);
}

long long dp[105][105];

int main(int argc, char* argv[]) {
	init();
	int i, j, n, k;
	for(i = 1; i <= 100; i++) {
		for(j = 1; j <= 100; j++) {
//			printf("i = %d, j = %d", i, j);
			if(j <= 1) dp[i][j] = 1;
			else if(i <= 1) dp[i][j] = j;
			else dp[i][j] = dp[i-1][j] + dp[i][j-1];
			dp[i][j] %= 1000 * 1000;
		}
	}
	scanf("%d%d", &n, &k);
	while(n && k) {
		printf("%lli\n", dp[n][k]);
		scanf("%d%d", &n, &k);
	}
	return 0;
}
