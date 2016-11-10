#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	int i;
	long res = 1;
	scanf("%i", &n);
	for (i = 2; i <= n; ++i) {
		res *= i;
	}
	printf("%li", res);
	return 0;
}
