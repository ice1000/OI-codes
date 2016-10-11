#include <stdio.h>

long long a[105][105];

int main(int argc, char *argv[]) {
	long long n, m, i, j, max = -1;
	// freopen("brick.in", "r", stdin);
	// freopen("brick.out", "w", stdout);
	scanf("%I64d %I64d", &n, &m);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			scanf("%i", &a[i][j]);
	for (i = 0; i < n + m; ++i)
		for (j = 0; j < n + m; ++j)
			int x;
	return 0;
}
