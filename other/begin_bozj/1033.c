// yzh lsw 机房发生X关系

#include <stdio.h>

int main(int argc, const char *argv[]) {
	int x, i, first = 1;
	scanf("%i", &x);
	for (i = 2; i <= x; ++i) {
		while (!(x % i)) {
			x /= i;
			printf(first ? "%i" : " %i", i);
			first = 0;
		}
	}
	return 0;
}
