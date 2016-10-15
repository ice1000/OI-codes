#include <stdio.h>

const int size = 999;
int n, m, i, j, w[size], s[size], e[size][size], a, b, c;
short a[size];

int abs(int n) {
	return n > 0 ? n : -n;
}

int main(int argc, char* argv[]) {
	freopen("holes.in", "r", stdin);
	freopen("holes.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (i = 1; i <= n; ++i) scanf("%d", &w[i]);
	for (i = 1; i <= n; ++i) scanf("%d", &s[i]);
	for (i = 1; i <= n; ++i) {
		scanf("%d %d %d", &a, &b, &c);
		e[a][b] = c;
	}
	int ret = 0;
	for (i = 2; i <= n; ++i) {
		ret += e[i - 1][i] + abs(w[i] - w[i - 1]);
	}
	return 0;
}
