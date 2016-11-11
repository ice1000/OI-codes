// yzh lsw 机房发生X关系

#include <stdio.h>

void print_binary(int n) {
	if (n) {
		print_binary(n >> 1);
		putchar(n & 1 ? '1' : '0');
	}
}

int main(int argc, const char *argv[]) {
	int x;
	scanf("%i", &x);
	print_binary(x);
	return 0;
}
