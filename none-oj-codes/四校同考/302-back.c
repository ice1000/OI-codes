#include <stdio.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define lowbit(x) ((x) & (-(x)))

int color[1001][1001];
int n, c, m, a, b;

void add(int idx, int van, int value) {
	if (van <= n) {
		color[idx][van] += value;
		add(idx, van + lowbit(van), value);
	}
}

int sum(int idx, int edge) {
	return edge ? color[idx][edge] +
			sum(idx, edge - lowbit(edge)) : 0;
}

int main(int argc, char *argv[]) {
	int i, j;
	scanf("%i %i", &n, &c);
	for (i = 0; i < n; ++i) {
		scanf("%i", &j);
		// FIXME
		add(j, i, 1);
	}
	printf("233");
	scanf("%i", &m);
	for (i = 0; i < m; ++i) {
		scanf("%i %i", &a, &b);
		for (j = 0; i < c; ++j) {
			if (sum(j, b) - sum(j, a) > ((a + b) >> 1)) {
				printf("yes %i\n", j);
				break;
			}
		}
		if (j >= c) {
			printf("no\n");
		}
	}
	return 0;
}

/*
10 3
1 2 1 2 1 2 3 2 3 3
8
1 2
1 3
1 4
1 5
2 5
2 6
6 9
7 10
*/
