#include <stdio.h>

inline int get(int num, int m) {
	int ret = 0;
	do {
		if (num % 10 == m) ++ret;
	} while (num /= 10);
	return ret;
}

int main(int argc, char *argv[]) {
	int q, i, j = 0, n;
	scanf("%i %i", &n, &q);
//	printf("%i", get(n, q));
	for (i = 1; i <= n; ++i) {
		j += get(i, q);
	}
	printf("%i", j);
	return 0;
}


