#include <bits/stdc++.h>

#define __abs(x) (x) > 0 ? (x) : (-(x))

int seq[1000005], fuck[10000005], index_fuck;

int main(int argc, char *argv[]) {
	freopen("mark.in", "r", stdin);
	freopen("mark.out", "w", stdout);
	int n, k, i, j, a;
	scanf("%i %i", &n, &k);
	for (i = 0; i < n; ++i) scanf("%i", &seq[i]);
	std::sort_heap(seq, seq + n);
	for (i = 0; i < n - 1; ++i) {
		for (j = i + 1; j < n; ++j) {
			fuck[index_fuck++ % 10000005] = __abs(seq[i] - seq[j]);
		}
	}
	std::sort_heap(fuck, fuck + index_fuck);
	n = 0;
	for (i = 0; i < k; ++i) n += fuck[i];
	printf("%i\n", n);
	return 0;
}
/*
5 5 5 3 1 4 2
*/