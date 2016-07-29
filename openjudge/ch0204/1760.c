#include <stdio.h>

int save[1000005];
int fib(int n) {
	if (n == 2 || n == 1) return 1;
	return save[n] ? save[n] : (save[n] = (fib(n - 1) + fib(n - 2)) % 1000);
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
