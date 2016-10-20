#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init() {
	freopen("teacher.in", "r", stdin);
	freopen("teacher.out", "w", stdout);
}

int x[100001], y[100001];
char mark[200001];

int main(int argc, char *argv[]) {
	init();
	int t, n, m, i, j, k;
	scanf("%i", &t);
	while (t--) {
		memset(mark, 0, sizeof(mark));
		scanf("%i %i", &n, &m);
		for (i = 0; i < n; ++i) {
			scanf("%i %i", &x[i], &y[i]);
		}
		if (n <= 2) {
			printf("NO\n");
			continue;
		}
		k = 0;
		for (i = 1; i < n; ++i) {
			for (j = 0; j < i; ++j) {
				k = abs(x[i] - x[j]) + abs(y[i] - y[j]);
				++mark[k];
				if (mark[k] >= 2) {
					printf("YES\n");
					goto out;
				}
			}
		}
		printf("NO\n");
out:
		;
	}
	return 0;
}

/*
3
3 10
1 1
2 2
3 3
4 10
8 8
2 3
3 3
4 4
5 10
1 1
2 2
5 5
3 2
2 3
*/

