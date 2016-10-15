/*
作者:千里冰封
题目:p2834 斐波那契数
*/

#include <stdio.h>
#include <stdlib.h>

int *cache, p;
int fib(int n) {
	if (n < 3) return 1;
	if (cache[n]) return cache[n];
	return (cache[n] = (fib(n - 1) + fib(n - 2)) % p);
}

int main(int argc, char* argv[]) {
	int i, n, m;
	scanf("%d %d %d", &n, &p, &m);
	cache = (int *) malloc(1001 * sizeof(int));
	for (i = 0; i < 1001; ++i) cache[i] = 0;
	for (i = 1; i <= m; ++i) if (fib(i) == n) {
		printf("%d\n", i);
		break;
	}
	if (i > m) printf("-1\n");
	free(cache);
	return 0;
}
