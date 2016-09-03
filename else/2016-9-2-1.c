#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int i, n;
	long long a, b;
	scanf("%I64d", &n);
	while (n--) {
		scanf("%I64d", &a);
		b = sqrtl(a);
		for (i = 2; i * i <= b; ++i)
			if (!(b % i)) break;
		printf("%s\n", b * b == a && i * i > b && a > 1 ? "YES" : "NO");
	}
	return 0;
}
