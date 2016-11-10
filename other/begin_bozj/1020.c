#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	int i;
	long res = 0;
	scanf("%i", &n);
	for (i = 1; i <= n; ++i) {
		res += i * i;
	}
	printf("%li", res);
	return 0;
}
