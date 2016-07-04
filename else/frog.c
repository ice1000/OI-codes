#include <stdio.h>

void init() {
	freopen("frog.in", "r", stdin);
	freopen("frog.out", "w+", stdout);
}

long long pow(int y) {
	long long x = 1;
	while(y--) x *= 2;
	return x;
}

int main(int argc, char* argv[]) {
	init();
	int n;
	scanf("%d", &n);
	printf("%I64d", pow(--n));
	return 0;
}
