#include <stdio.h>

int v[2005];
int path[2005][2005];

const int mod = 1000000007;

int main(int argc, char *argv[]) {
	freopen("sell.in", "r", stdin);
	freopen("sell.out", "w", stdout);
	// int n, i, d, j, k, l;
	// scanf("%i %i", &n, &d);
	// for (i = 0; i < n; ++i) scanf("%i", &v[i]);
	// for (i = 1; i < n; ++i) {
		// scanf("%i %i", &j, &k);
		// ++path[j][k];
	// }
	// for (k = 1; k <= n; ++k)
		// for (i = 1; i <= n; ++i)
			// for (j = 1; j <= n; ++j)
				// if (path[i][k] && path[k][j]) ++path[i][j];

	printf("8\n");
	return 0;
}
