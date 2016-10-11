#include <stdio.h>

typedef long long ll;

ll a[100009], n, k, result;
short capital[100009];
short save[100009];

int main (int argc, char *argv[]) {
	scanf("%I64d %I64d", &n, &k);
	ll i, j;
	for (i = 0; i < n; ++i) scanf("%I64d", &a[i]);
	for (i = 0; i < k; ++i) {
		scanf("%I64d", &save[i]);
		capital[save[i] - 1]++;
	}
	if (!capital[0] && !capital[n - 1]) i = 0, result += a[i] * a[n - 1];
	for (i = 0; i < n - 1; ++i) {
		result += a[i] * a[i + 1];
		for (j = i + 2; j < n; ++j)
			if (capital[i] || capital[j])
				result += a[i] * a[j];
	}
	printf("%I64d\n", result);
	return 0;
}
/*
 * 4 1 2 3 1 2 3
 */
