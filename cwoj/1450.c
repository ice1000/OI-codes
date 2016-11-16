#include <stdio.h>
#include <stdlib.h>

#define number long long
#define size 1000100

int cmp(const void *a, const void *b) {
	return (int) (*(number *) a - *(number *) b);
}

number a[size];

int main(int argc, const char *argv[]) {
	number i, j = 0LL, c;
	size_t n;
	scanf("%lli", &n);
	for (i = 1LL; i <= n; ++i) {
		scanf("%lli", &a[i]);
	}
	qsort(a + 1, n, sizeof(a[0]), cmp);
	for (i = 1LL; i <= n; ++i) {
		j += (a[i] - a[i - 1]) * ((i << 1) - 1) * (n - i + 1);
	}
	number n1 = j, m = n;
	for (; m > 0; c = n1 % m, n1 = m, m = c);
	i = n1;
	printf("%lli %lli", j / i, n / i);
	return 0;
}
