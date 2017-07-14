#include <stdio.h>

typedef unsigned long long ull;

ull *eval(ull n){
	ull n1 = n;
	static ull a[2];
	a[0] = a[1] = 0;
	ull pa = 1;
	ull pb = 1;
	while (n) {
		int x = n % 10;
		if (x & 1) {
			a[1] += x * pa;
			pa *= 10;
		} else {
			a[0] += x * pb;
			pb *= 10;
		}
		n /= 10;
	}
	printf("%llu %llu %llu\n", n1, a[0], a[1]);
	return a;
}
