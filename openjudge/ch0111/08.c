#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int cmp(const void *a, const void *b) {
	return *((int *) a) - *((int *) b);
}

int a[100001];

int main(int argc, char *argv[]) {
	int i, j, n;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%i", &a[i]);
	}
	qsort(a, n, sizeof(a[0]), cmp);
	printf("%i", a[0]);
	argc = a[0];
	for (i = 1; i < n; ++i) {
		if (a[i] != argc) {
			printf(" %i", a[i]);
			argc = a[i];
		}
	}
	return 0;
}