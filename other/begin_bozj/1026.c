#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	int i, j;
	scanf("%i", &n);
	if (n == 1) {
		puts("F");
	} else {
		for (i = 2; i * i <= n; ++i) {
			if (!(n % i)) {
				puts("F");
				break;
			}
		}
		if (i * i > n) {
			puts("T");
		}
	}
	return 0;
}