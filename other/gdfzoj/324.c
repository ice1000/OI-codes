#include <stdio.h>

int main(int argc, char *argv[]) {
	int i, a = 1, n;
	scanf("%i", &n);
	for (i = n; i > 2; --i) {
		a *= i;
	}
	printf("%i", a);
	return 0;
}
