#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	int i;
	double res = 0;
	scanf("%i", &n);
	for (i = 1; i <= n; ++i) {
		res += 1.0 / i;
	}
	printf("%.3lf", res);
	return 0;
}