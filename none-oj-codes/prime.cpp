#include <bits/stdc++.h>

int cnt, n, i, j, k = 2, l = 0, p = 1, q = 1, r, m;
const int size = 150000;
bool prime[size + 1];

int gcd(int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

inline bool isPrime(int i) {
	if (i == 2) return true;
	for (j = 3; j * j <= i; j += 2) if (!(i % j)) return false;
	return true;
}

inline bool shit(int i) {
	return prime[i];
}

inline void fuck() {
	r = (q * l * k + p);
	m = (p * l * k);
	int gg = gcd(r, m);
	q = r / gg;
	p = m / gg;
}

int main(int argc, char *argv[]) {
	freopen("prime.in", "r", stdin);
	freopen("prime.out", "w", stdout);
	for (i = 2; i < size; ++i) prime[i] = isPrime(i);
	scanf("%i", &cnt);
	while (cnt--) {
		scanf("%i", &n);
		p = q = 1;
		for (j = 2; j <= n; ++j) {
			if (!shit(j)) {
				fuck();
				continue;
			}
			i = k = l = 0;
			while (!l or !k) {
				if (!l and shit(j - i)) l = j - i;
				else if (!k and shit(j + i)) k = j + i;
				++i;
			}
			fuck();
		}
		printf("%i/%i\n", q - p, p);
	}
	return 0;
}
