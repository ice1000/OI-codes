#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	int i, j, min, max;
	scanf("%i %i", &n, &max);
	min = max;
	for (i = 1; i < n; ++i) {
		scanf("%i", &j);
		if (j > max) max = j;
		if (j < min) min = j;
	}
	printf("%i %i", max, min);
	return 0;
}