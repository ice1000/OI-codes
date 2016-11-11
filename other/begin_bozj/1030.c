// yzh lsw 机房发生X关系

#include <stdio.h>

int main(int argc, const char *argv[]) {
	int i, j, x;
	double n = 0;
	scanf("%i", &x);
	for (i = 1; n < x; ++i) {
		n += 1.0 / i;
//		printf("%.2lf\n", n);
	}
	printf("%i", --i);
	return 0;
}
