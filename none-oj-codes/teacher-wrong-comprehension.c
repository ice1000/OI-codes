#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init() {
	freopen("teacher.in", "r", stdin);
	freopen("teacher.out", "w", stdout);
}

typedef struct {
	int x;
	int y;
} point;

point ps[100001];
char mark[100001];

int compare(const void *l, const void *r) {
	return ((point *) l)->x >= ((point *) r)->x;
}

int main(int argc, char *argv[]) {
	init();
	int t, n, m, i, j, k;
	scanf("%i", &t);
	while (t--) {
		memset(mark, 0, sizeof(mark));
		scanf("%i %i", &n, &m);
		for (i = 0; i < n; ++i) {
			scanf("%i %i", &ps[i].x, &ps[i].y);
		}
		if (n <= 2) {
			puts("NO");
			continue;
		}
		qsort(ps, n, sizeof(ps[0]), compare);
		k = 0;
		for (i = 1; i < n; ++i) {
//			printf("<%i, %i>\n", ps[i].x, ps[i].y);
			for (j = 0; j < i; ++j) {
				if (ps[i].x != ps[j].x && ps[i].y > ps[j].y) {
					++mark[ps[i].x - ps[j].x + ps[i].y - ps[j].y];
				}
			}
		}
		for (i = 0; i < m; ++i) {
//			printf("[%i]", mark[i]);
			if (mark[i] >= 2) {
				puts("YES");
				break;
			}
		}
//		printf("|%i|\n", k);
		if (i >= m) {
			puts("NO");
		}
	}
	return 0;
}

/*
2
3 10
1 1
2 2
3 3
4 10
8 8
2 3
3 3
4 4
*/
