// yzh lsw 机房发生X关系

#include <stdio.h>
#include <limits.h>

#define __abs(a) ((a) > 0 ? (a) : (-(a)))

int main(int argc, const char *argv[]) {
	int x, i, j = INT_MAX;
	scanf("%i", &x);
	for (i = 1; i < INT_MAX >> 1; i <<= 1) {
		if (__abs(i - x) < __abs(j - x)) {
			j = i;
		}
	}
	printf("%i", j);
	return 0;
}
