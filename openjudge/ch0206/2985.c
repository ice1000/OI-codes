#include <stdio.h>
#include <string.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int a[2001], n, m, dp[2001] = { 1 };

int main(int argc, char *argv[]) {
	int i, j;
	scanf("%i %i", &n, &m);

	for (i = 1; i <= n; ++i) {
		scanf("%i", &a[i]);
	}

	for (i = 1; i <= n; ++i) {
		for (j = m; j >= a[i]; --j) {
			dp[j] += dp[j - a[i]];
		}
	}

	printf("%i", dp[n]);

	return 0;
}
/**
5 5
1 2 3 4 5
*/



