#include <stdio.h>

int fun(int n) {
	int j = 0, i = n + 1;
	while (i--) {
		if (i % 3 == 2 && i % 5 == 3 && i % 7 == 2) ++j;
	}
	printf("[%i, %i]\n", n, j);
	return j;
}

int main(int argc, const char *argv[]) {
	int i = 1, j = 0;
	while (++i) {
		fun(i);
	}
	return 0;
}
