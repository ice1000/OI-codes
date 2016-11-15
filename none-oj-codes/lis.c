#include <stdio.h>

#define size 200010

int n, a[size], dp[size], idx, prefix[size];

int bsearch(int l, int r, int value) {
	if (l >= r) return l;
	int mid = (l + r) >> 1;
	if (dp[mid] >= value) return bsearch(l, mid, value);
	return bsearch(++mid, r, value);
}

int main(int argc, const char *argv[]) {
//	freopen("lis.in", "r", stdin);
//	freopen("lis.out", "w", stdout);
	int i, j, k = 0;
	idx = 1;
	scanf("%i", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%i", &a[i]);
		prefix[i] = prefix[i - 1];
		if (!a[i]) ++prefix[i];
	}
	for (i = 1; i <= n; ++i) {
		if (a[i]) a[i] -= prefix[i - 1];
	}
	dp[1] = a[1];
	for (i = 2; i <= n; ++i) {
		if (a[i] > dp[idx])
			dp[++idx] = a[i];
		else
			dp[bsearch(1, idx, a[i])] = a[i];
	}
//	for (i = 1; i <= n; ++i) {
//		printf("<%i>\n", dp[i]);
//	}
	printf("%i", idx + prefix[n] - 1);
	return 0;

}

/*
9
0 2 0 2 1 2 0 5 0
*/

