#include <stdio.h>

#define size 100010 << 1
#define __max(a, b) (((a) > (b)) ? (a) : (b))
#define __min(a, b) (((a) < (b)) ? (a) : (b))

char str[10001];

int main(int argc, const char *argv[]) {
	freopen("welcome.in", "r", stdin);
	freopen("welcome.out", "w", stdout);
	int i, j, k, l, n;
	scanf("%i %i %s", &n, &k, str);
	printf("%i", --n >> 1);
	return 0;
}

/*
3
1 2 2
6 6 2
7 8 4
*/
