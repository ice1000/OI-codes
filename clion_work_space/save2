/*
作者:千里冰封
*/

#include <stdio.h>

const int size = 500 + 5;

int n, m, s, t;
int min_distance[size][size];
int max_distance[size][size];

int min(int x, int y) {
	return x > y ? y : x;
}

double min_with_double(double x, double y, double z) {
	return x > y / z ? y / z : x;
}

int max(int x, int y) {
	return x < y ? y : x;
}

void init() {
	freopen("village.in", "r", stdin);
	freopen("village.out", "w+", stdout);
}

int main(int argc, char *argv[]) {
	init();
	int i, j, k;
	scanf("%i %i", &n, &m);
	for ( i = 0; i < m; i++ ) {
		int a, b, l;
		scanf("%i %i %i", &a, &b, &l);
		min_distance[a][b] = l;
		min_distance[b][a] = l;
		max_distance[a][b] = l;
		max_distance[b][a] = l;
	}
	for ( k = 1; k <= n; k++ )
		for ( i = 1; i <= n; i++ )
			for ( j = 1; j <= n; ++j ) {
				min_distance[i][j] = min(
						min_distance[i][j],
						min_distance[i][k] + min_distance[k][j]
				);
				max_distance[i][j] = max(
						max_distance[i][j],
						max_distance[i][k] + max_distance[k][j]
				);
			}
	scanf("%i %i", &s, &t);
	int x, y;

	return 0;
}
