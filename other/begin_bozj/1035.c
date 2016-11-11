// yzh lsw 机房发生X关系

#include <stdio.h>

int main(int argc, const char *argv[]) {
	int x, i, shit = 0;
	scanf("%i", &x);
	for (i = 1; i <= x; ++i) {
		if (!(x % i)) {
			shit += i;
		}
	}
	printf("%i", shit);
	return 0;
}
