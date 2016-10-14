#include <bits/stdc++.h>

int x[205], y[205], a[40005], b[40005];

int isParallel(int i, int j) {
	return !(a[i] * b[j] - a[j] * b[i]);
}

int main(int argc, char *argv[]) {
	int n, i, j, k = 0, res = 0;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) scanf("%i %i", &x[i], &y[i]);
	for (i = 0; i < n; ++i)
		for (j = i + 1; j < n; ++j) {
			a[k] = x[i] - x[j];
			b[k++] = y[j] - y[j];
		}
	printf("k = %i\n", k);
	for (i = 0; i < k; ++i)
		for (j = i + 1; j < k; ++j)
			if (!isParallel(i, j)) ++res;
			else printf("%i %i %i %i\n", a[i], b[i], a[j], b[j]);
	printf("%i\n", (k * k + k) / 2 - res);
	return 0;
}
/*
4 -1 1 -2 0 0 0 1 1
*/