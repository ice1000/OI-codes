#include <stdio.h>

long long save[1001];
long long fib(int n) {
	if (!n || n == 1) return 1;
	return save[n] ? save[n] : (save[n] = fib(n - 1) + fib(n - 2));
}

int main(int argc, char* argv[]) {
	int i;
	while(scanf("%d", &i) != EOF) printf("%lli\n", fib(i));
	return 0;
}
