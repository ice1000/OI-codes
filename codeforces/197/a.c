#include <stdio.h>

int main(int argc, char* argv[]) {
	int a, b, c, win = 1;
	scanf("%d %d %d", &a, &b, &c);
	c += c;
	printf("%s", a >= c && b >= c ? "First" : "Second");
	return 0;
}

