#include <stdio.h>

int f(int a, int b) {
	if (b > a) return f(a, a);
	if (!a || b == 1) return 1;
	return f(a, b - 1) + f(a - b, b);
}

int main(int argc, char *argv[]) {
	int t, a, b;
	scanf("%i", &t);
	while (t--) {
		scanf("%i %i", &a, &b);
		printf("%i\n", f(a, b));
	}
}