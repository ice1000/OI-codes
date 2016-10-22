#include <stdio.h>
#include <string.h>

#define shit(a) for (a = 1; a < n; ++a) 

int n, m, q, map[2001][2001], max[2001][2001];

int main(int argc, char *argv[]) {
//	freopen("travel.in", "r", stdin);
//	freopen("travel.out", "w", stdout);
	int i, j, a, b, c;
	memset(map, 0xff, sizeof(map));
	memset(max, 0xff, sizeof(max));
	scanf("%i %i %i", &n, &m, &q);
	for (i = 0; i < m; ++i) {
		scanf("%i %i %i", &a, &b, &c);
		map[a][b] = c;
		max[a][b] = c;
	}
	///
	shit (a) {
		shit (b) {
			shit (c) {
				if (map[])
			}
		}
	}
	return 0;
}
