#include <stdio.h>

#define __abs(x) ((x) > 0 ? (x) : (-(x)))
#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))

int main (int argc, char *argv[]) {
	int x1, x2, x3;
	scanf("%i %i %i", &x1, &x2, &x3);
	printf("%i", __max(x1, __max(x2, x3)) -
	             __min(x1, __min(x2, x3)));
	return 0;
}




