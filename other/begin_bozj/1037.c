#include <stdio.h>

int fast_pow(int, int, int);

int fast_plus(int, int, int);

int main(int argc, const char *argv[]) {
	int a, b, m;
	scanf("%i %i %i", &a, &b, &m);
	printf("%i", fast_pow(a, b, m));
	return 0;
}

int fast_plus(int a, int b, int m) {
	int ret = 0;
	while (b) {
		if (b & 1) {
			ret = (ret + a) % m;
		}
		b >>= 1;
		a = (a << 1) % m;
	}
	return ret;
}

int fast_pow(int a, int b, int m) {
	int ret = 1;
	while (b) {
		if (b & 1) {
			ret = fast_plus(ret, a, m);
		}
		b >>= 1;
		a = fast_plus(a, a, m);
	}
	return ret;
}