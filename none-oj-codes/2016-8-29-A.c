#include <stdio.h>

typedef long long ll;

ll a[100009], n, k, result, fuck;
short capital[100009];

int main (int argc, char *argv[]) {
	scanf("%I64d %I64d", &n, &k);
	ll i, j;
	for (i = 1; i <= n; ++i) {
		scanf("%I64d", &a[i]);
		fuck += a[i];
	}
	for (i = 1; i <= k; ++i) {
		scanf("%I64d", &j);
		capital[j]++;
	}
	for (i = 1; i <= n; ++i)
		if (capital[i]) {
			fuck -= a[i];
			result += fuck * a[i];
		}
	if (!capital[1] && !capital[n]) result += a[1] * a[n];
	for (i = 1; i < n; ++i) {
		if (!capital[i] && !capital[i + 1])
			result += a[i] * a[i + 1];
	}
	printf("%I64d\n", result);
	return 0;
}
/*
 * 4 1 2 3 1 2 3
 * 5 2 3 5 2 2 4 1 4
 */