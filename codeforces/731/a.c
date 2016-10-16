#include <stdio.h>

inline int abs(int a) {
	return a > 0 ? a : -a;
}

inline int max(int a, int b) {
	return a < b ? a : b;
}

char a[10001];

int getMin(char x, char y) {
	return max(abs(x - y), 26 - abs(x - y));
}

int main(int argc, char *argv[]) {
	a[0] = 'a';
	gets(a + 1);
	int i, res = 0;
	for (i = 1; a[i] != '\0'; ++i) {
		res += getMin(a[i], a[i - 1]);
	}
	printf("%i", res);
	return 0;
}
