#include <stdio.h>

char fuck[100001] = "a";

int max(int a, int b) {
	return a > b ? a : b;
}

int exist(int n, char dick) {
	int i = 0;
	while (n - ++i >= max(n - 4, 0))
		if (i != 4 && i != 7 && fuck[n - i] == dick) return 1;
	return 0;
}

int main(int argc, char* argv[]) {
	int n, i;
	char b, c;
	scanf("%d", &n);
	for (i = 1; i < n; i++) {
		b = 'a' - 1;
		while (++b) if (!exist(i, b)) {
			fuck[i] = b;
			break;
		}
	}
	printf("%s", fuck);
	return 0;
}
