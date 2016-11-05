#include <stdio.h>

#define mod1 1000
#define int long long

int k, x, g = 1, tot;
int mem[5001][5001];

int f(int a, int b) {
	if (b > a) return f(a, a);
	if (mem[a][b]) return mem[a][b];
	if (a <= 1 || b == 1) return 1;
	return mem[a][b] = (f(a, b - 1) + f(a - b, b));
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
	int i, j;
	scanf("%lli %lli", &k, &x);
	for (i = 0; i < x; ++i) {
		g = (g * x) % mod1;
	}
	if (k > g) {
		puts("0");
	} else if (k == g) {
		puts("1");
		return 0;
	} else {
		printf("%lli", f(g - k, k) * k);
	}
	return 0;
}

/*
3 3
*/
