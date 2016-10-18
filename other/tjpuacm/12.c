#include <stdio.h>

int dp[10001];
int seq[10001];

int main(int argc, char *argv[]) {
	int i, j, n, max;
	while (scanf("%i", &n) != EOF) {
		max = 1;
		for (i = 0; i < n; ++i) {
			scanf("%i", &seq[i]);
			dp[i] = 1;
		}
		for (i = 1; i < n; ++i) {
			if (seq[i] > seq[i - 1] && dp[i- 1] + 1 > dp[i]) {
				dp[i] = dp[i - 1] + 1;
				if (dp[i] > max) {
					max = dp[i];
				}
			}
		}
		printf("%i\n", max);
	}
	return 0;
}
