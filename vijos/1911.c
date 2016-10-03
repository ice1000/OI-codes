#include <stdio.h>

int bucket[10 * 1000 + 5];

int main(int argc, char *argv[]) {
	int i, j, n, m = 0;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%i", &j);
		++bucket[j];
	}
	for (i = 1; i <= sizeof(bucket) / sizeof(bucket[0]); ++i) {
		if (bucket[i])
			for (j = 1; j < ((i + 1) >> 1); ++j) {
				if (bucket[i - j] && bucket[j]) {
					++m;
//					printf("%i ", i);
					break;
				}
			}
	}
	printf("%i", m);
	return 0;
}
/*
4 1 2 3 4
*/
