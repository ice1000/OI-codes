#include <stdio.h>

int main(int argc, const char *argv[]) {
	freopen("choco.in", "r", stdin);
	freopen("choco.out", "w", stdout);
	int n, a, b;
	while (scanf("%i %i %i", &n, &a, &b) != EOF) puts(n % (a + b) >= a ? "1" : "0");
	return 0;
}

