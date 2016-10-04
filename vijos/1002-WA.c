#include <stdio.h>

int a[10001];

int find (int l, int r, int n) {
	if (l > r) return -1;
	if (l == r) return r;
	int mid = (l + r) >> 1;
	return a[mid] == n ? mid : a[mid] > n ? find(l, mid, n) : find(mid + 1, r, n);
}

int main (int argc, char *argv[]) {
	int l, i, index = 0, s, t, m, count = 0;
	scanf("%i %i %i %i", &l, &s, &t, &m);
	for (i = 0; i < m; ++i) scanf("%i", &a[i]);
	for (i = m; i < m + t + 10; ++i) {
		a[i] = l;
	}
	while (index < m) {
		index = find(index + s, index + t, index + t);
//		printf("%i ", index);
		++count;
//		if (v == -1) break;
	}
	printf("%i\n", count - 1);
	return 0;
}


