#include <stdio.h>

int mark[502][502];

int main(int argc, char *argv[]) {
	const char *format = "%i %i\n";
	int n, m, v, i, j, k;
	scanf("%i %i %i", &n, &m, &v);
	if (m > (n * (n - 3) + 4) / 2 || m < n - 1 || n < 3)
		printf("-1\n");
	else {
		for (i = 1; i <= n; ++i)
			if (i - v) printf(format, i, v);
		m -= n - 1;
		k = v == 1 ? 2 : 1;
		for (i = 1; i <= n && m; ++i)
			if (i - v && i - k)
				for (j = i + 1; j <= n && m; ++j)
					if (j - v && j - k) printf(format, i, j), --m;
	}
	return 0;
}
