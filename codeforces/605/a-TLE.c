#include <stdio.h>
#include <string.h>

#define __max(x, y) ((x) > (y) ? (x) : (y))

int a[100001], dp[100001];

int find(int l, int r, int n) {
	if (l >= r) return l;
	int mid = (l + r) >> 1;
	return dp[mid] == n ? mid : dp[mid] > n ? find(l, mid, n) : find(mid + 1, r, n);
}

int main(int argc, char *argv[]) {
	int i, j, n, m = 0;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) scanf("%i", &a[i]);
	for (i = 0; i < n; ++i) {
		if (a[i] > dp[m]) dp[++m] = a[i];
		else dp[find(0, m, a[i])] = a[i];
	}
	printf("%i", n - m);
	return 0;
}
