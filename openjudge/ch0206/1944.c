#include <stdio.h>
#include <string.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int main(int argc, char *argv[]) {
	int i, a[1001] = {1, 2}, n;
	scanf("%i", &n);

	for (i = 2; i < n; ++i)
		a[i] = a[i - 1] + a[i - 2];

	printf("%i", a[--n]);

	return 0;
}
/**
*/

