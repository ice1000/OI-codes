#include <stdio.h>
#include <stdlib.h>

char bucket[100000005];
int n;

//int get() {
//	static int i = 1;
//	while (!bucket[i]) ++i;
//	if (i >= n) return -1;
//	--bucket[i];
//	return i;
//}
//
int main(int argc, char *argv[]) {
	int i, j;
	long long m = 0, max = -1;

	scanf("%i", &n);

	for (i = 1; i <= n; ++i) {
		scanf("%i", &j);
		++bucket[j];
		if (j > max) max = j;
	}

	for (i = 0; i <= max; ++i) {
		if (bucket[i] > 0) {
			--bucket[i];
			for (j = i; j <= max; ++j) {
				if (bucket[j] > 0) {
					--bucket[j];
					++bucket[i + j];
					if (i + j > max) max = i + j;
					m += i + j;
					break;
				}
			}
		}
		if (bucket[i] > 0)
			--bucket[i];
	}

	printf("%I64d", m);
	
}
/*
4 1 2 3 4
 */

