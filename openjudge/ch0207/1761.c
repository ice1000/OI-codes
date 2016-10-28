#include <stdio.h>

int n, m, a, b[1001] = { 1 };
int main(int argc, const char *argv[]) {
  int i, j;
	scanf("%i", &n);
	for(i = 1; i <= n; ++i) {
		scanf("%i", &a);
		for(j = 400; j >= a; --j) {
			b[j] = (b[j] + b[j - a]) % 10000;
		}
	}
	printf("%i", b[400]);
	return 0;
}
