#include <stdio.h>

int main(int argc, char* argv[]) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	c += c;
	printf("%s", (a / c) * (b / c) % 2 ? "First" : "Second");
	return 0;
}
