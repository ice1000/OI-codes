#include <stdio.h>
#include <math.h>

#define size 200005

// ²¢²é¼¯

int c[size], l[size], r[size], uset[size];
int n, m, k, tot;

int find(int a) {
	return uset[a] == a ? a : find(uset[a]);
}

void merge(int x, int y) {
	if (find(x) != find(y)) uset[x] = y, ++tot;
}

int main(int argc, char *argv[]) {
	int i, j, x, y, z;
	scanf("%i %i %i", &n, &m, &k);
	for (i = 0; i < n; ++i) scanf("%i", &c[i]);
	for (i = j = 0; j < m; ++j) {
		scanf("%i %i", &l[i], &r[i]);
		if (c[l[i]] != c[r[i]]) ++i;
	}
	if (!i) {
		putchar('0');
		return 0;
	}
	m = i;
	for (i = 0; i < m; ++i) {
		merge(l[i], r[i]);
	}
	printf("%i", tot);
	return 0;
}

