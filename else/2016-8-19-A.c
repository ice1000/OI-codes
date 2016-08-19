#include <stdio.h>

int main(int argc, char* argv[]) {
	int n, i;
	scanf("%d", &n);
	if (n == 1)
		printf("-1\n");
	else if (n & 1) {
//		TODO
//		for (i = 2; i <= n; ++i)
//			printf("%d ", i);
		printf("-1\n");
	} else {
		for (i = 1; i < n; i += 2)
			printf("%d %d ", i + 1, i);
	}
	return 0;
}
