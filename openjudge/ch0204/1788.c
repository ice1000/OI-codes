#include <stdio.h>

int save[1000005];
int fib(int n) {
	if (n < 3) return 1;
	return save[n] ? save[n] : (save[n] = (2 * fib(n - 1) + fib(n - 2)) % 32767);
}

int main(int argc, char* argv[]) {
	int n, i;
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &i);
		printf("%d\n", fib(i));
	}
	return 0;
}
