#include <stdio.h>

int a[102][102][102];

int main(int argc, char *argv[]) {
	int n, m, q, i, j, k, l, u, v;
	scanf("%d %d", &n, &m);
	for (i = 0; i < m; ++i) {
		scanf("%d %d %d", &j, &k, &l);
		if (!a[j][k][l]) ++a[j][k][0], ++a[k][j][0];
		a[j][k][l] = 1, a[k][j][l] = 1;
	}
	for (k = 1; k <= n; ++k)
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j)
				for (l = 1; l <= m; ++l)
					if (a[i][k][l] && a[k][j][l]) {
						if (!a[i][j][l]) ++a[i][j][0], ++a[j][i][0];
						a[i][j][l] = 1;
						a[j][i][l] = 1;
					}
	scanf("%d", &q);
	for (i = 0; i < q; ++i) {
		scanf("%d %d", &u, &v);
		printf("%d\n", a[u][v][0] ? a[u][v][0] : a[v][u][0]);
	}
	return 0;
}

/*
4 5 1 2 1 1 2 2 2 3 1 2 3 3 2 4 3 3 1 2 3 4 1 4

5 7 1 5 1 2 5 1 3 5 1 4 5 1 1 2 2 2 3 2 3 4 2 5 1 5 5 1 2 5 1 5 1 4
*/
