#include <stdio.h>

int gcd(int, int);

int main(int argc, const char *argv[]) {
	int i, j;
	scanf("%i %i", &i, &j);
	printf("%i", i * j / gcd(i, j));
	return 0;
}

int gcd(int i, int j) {
	if (j > i) return gcd(j, i);
	return !j ? i : gcd(j, i % j);
}