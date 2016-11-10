#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	scanf("%i", &n);
	printf("%i", (((n >> 1) + 1) * (n + 1)) >> 1);
	return 0;
}
