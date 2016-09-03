#include <stdio.h>

int a[502][502];
int b[502][502];
int d[502];

int main(int argc, char *argv[]) {
	int n, i, j, k, l, t;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]);
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) for (k = 1; k <= n; ++k) b[j][k] = a[j][k];
		for (k = 1; k <= n; ++k)
			if (!d[k]) for (j = 1; j <= n; ++j)
				if (!d[j]) for (l = 1; l <= n; ++l)
					if (!d[l] && b[j][k] + b[k][l] < b[j][l])
						b[j][l] = b[j][k] + b[k][l];
		t = 0;
		for (k = 1; k <= n; ++k)
			if (!d[k]) for (j = 1; j <= n; ++j)
				if (!d[j]) t += b[k][j];
		scanf("%d", &k);
		++d[k];
		printf("%d ", t);
	}
	return 0;
}
/*
2 0 5 4 0 1 2
*/
