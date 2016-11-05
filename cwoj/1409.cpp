#include <queue>
#include <stdio.h>

#define INF 0xffffff
#define size 200010 << 1

long long a[size];

int main(int argc, const char *argv[]) {
	int i, j, n, k;
	double min = INF, max = 0;
	scanf("%i %i", &n, &k);
	for (i = 1; i <= n; ++i) {
		scanf("%i", &j);
		a[i] = a[i - 1] + j;
		if (j < min) min = j;
		if (j > max) max = j;
	}
	if (k == 1) {
		printf("%.4lf", min);
		return 0;
	}
	while (max - min > 0.001) {
	}
	printf("%.4lf", );
	return 0;
}

/*
6 10 3 5 4 6 1 2
*/

