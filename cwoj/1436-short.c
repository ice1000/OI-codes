#include <stdio.h>
const int param_1[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368};
const int param_2[] = {1, 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657};
int main(int argc, const char *argv[]) {
	long long a, b, x;
	while (~scanf("%lli %lli %lli", &a, &x, &b)) (x - param_2[a]) % param_1[a] ? puts("-1") : printf("%lli\n", (x - param_2[a]) / param_1[a] * param_1[b] + param_2[b]);
	return 0;
}

