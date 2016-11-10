#include <stdio.h>

int n;

int main(int argc, const char *argv[]) {
	int i = 1, j = 0;
	scanf("%i", &i);
	++i;
	while (i--) {
		if (i % 3 == 2 && i % 5 == 3 && i % 7 == 2) ++j;
	}
	printf("%i\n", j);
	return 0;
}

