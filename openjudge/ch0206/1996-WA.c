#include <stdio.h>
#include <string.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int a[2001], n, dp[2001] = { 0xffffff }, m = 0, mm = 0;

int find(int l, int r, int n) {
	if (l >= r) return l;
	int mid = (l + r) / 2;
	return dp[mid] == n ? mid : dp[mid] > n ? find(l, mid, n) : find(mid + 1, r, n);
}

int main(int argc, char *argv[]) {
	int i, j;
	scanf("%i", &n);

	for (i = 0; i < n; ++i)
		scanf("%i", &a[i]);

	for (i = 0; i < n; ++i) {
		if (a[i] < dp[m]) dp[++m] = a[i];
		else dp[find(0, m, a[i])] = a[i];
	}

	memset(dp, 0, 2001 * sizeof(int));
	dp[0] = -1;

	for (i = n - 1; i >= 0; --i) {
		if (a[i] < dp[mm]) dp[++mm] = a[i];
		else dp[find(0, mm, a[i])] = a[i];
	}

	printf("%i", max(m, mm));

	return 0;
}
/**
8
186 186 150 200 160 130 197 220
*/

