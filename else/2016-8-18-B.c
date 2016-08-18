#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define __abs(x) (x) > 0 ? (x) : -(x)
#define __min(x, y) ((x) > (y) ? (y) : (x))

int n, k, dp[1000005];
int main(int argc, char* argv[]) {
	int i, j, kk, l;
	scanf("%d %d", &n, &k);
	if (k <= n) {
		printf("%d\n", __abs(n - k));
		return 0;
	}
	memset(dp, 1, n * sizeof(int));
	for (i = n + 1; i <= k + k; ++i) {
		if (i % 2) dp[i] = dp[i - 1] + 1;
		else dp[i] = __min(dp[i - 1], dp[i / 2]) + 1;
		for (j = i - 1, l = 1; j > n + (i - n) / 2; --j, l++)
			dp[j] = __min(dp[j], dp[i] + l);
	}
	printf("%d\n", dp[k]);
	return 0;
}
