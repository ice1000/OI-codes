#include <stdio.h>

long long pow(int y) {
	long long x = 1;
	while(y--) x *= 2;
	return x;
}

int main(int argc, char* argv[]) {
	int n;
	scanf("%d", &n);
	printf("%I64d", pow(--n));
	return 0;
}
