#include <stdio.h>

int main(int argc, const char *argv[]) {
	int i;
	scanf("%i", &i);
	printf("%i", i < 23 ? 0 : (i - 23) / 105 + 1);
	return 0;
}
