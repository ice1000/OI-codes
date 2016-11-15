#include <stdio.h>

int main(int argc, const char *argv[]) {
#define int long long
	freopen("super.in", "r", stdin);
	freopen("super.out", "w", stdout);
	int i, k, j, a, b, m, l, o, c, p, n;
	scanf("%lli", &n);
	while (n--) {
		scanf("%lli %lli", &a, &b);
		c = a + b;
		i = j = k = 0;
		l = o = p = 1;
		while (a) {
			m = a % 10;
			if (m) i += m * l, l *= 10;
			a /= 10;
		}
		while (b) {
			m = b % 10;
			if (m) j += m * o, o *= 10;
			b /= 10;
		}
		while (c) {
			m = c % 10;
			if (m) k += m * p, p *= 10;
			c /= 10;
		}
		if (i + j == k) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}

/*
3
101 102
11 33
120 45
 */
