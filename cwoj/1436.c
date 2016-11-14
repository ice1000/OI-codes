#include <stdio.h>

#define int long long

const int param_1[] = {
	0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89,
	144, 233, 377, 610, 987, 1597, 2584, 4181,
	6765, 10946, 17711, 28657, 46368
};

const int param_2[] = {
	1, 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89,
	144, 233, 377, 610, 987, 1597, 2584, 4181,
	6765, 10946, 17711, 28657
};

#undef int
int main(int argc, const char *argv[]) {
#define int long long
	int a, b, x;
//	for (int i = 0; i < 5; ++i) printf("%i\n", fun(list[i]));
//	int n = 100, i = j = 1; while (x --> 0) printf("%i\n", i + j), a = j, j += i, i = a;
	while (~scanf("%lli %lli %lli", &a, &x, &b)) {
		/// (param_1 * n + param_2)
		if ((x - param_2[a]) % param_1[a]) puts("-1");
		else printf("%lli\n", (x - param_2[a]) / param_1[a] * param_1[b] + param_2[b]);
	}
	return 0;
}

/**
 *   0      1      2      3      4      5      6      7
 * (0n+1) (1n+0) (1n+1) (2n+1) (3n+1) (5n+2) (8n+3) (13n+5)
 */

