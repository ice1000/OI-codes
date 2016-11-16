#include <stdio.h>
#include <stdlib.h>

#define number long long

number gcd(number n, number m) {
	number c;
	for (; m > 0; c = n % m, n = m, m = c);
	return n;
}

int cmp(const void *a, const void *b) {
  return *(number *)a - *(number *)b;
}

int main(int argc, const char *argv[]) {
	freopen("tourist.in", "r", stdin);
	freopen("tourist.out", "w", stdout);
	number i, j = 0LL, n;
	scanf("%lli", &n);
	for (i = 0LL; i < n; ++i) {
	  scanf("%lli", &a[i]);
  }
  qsort(a, n, sizeof(a[0]), cmp);
	for (i = 1LL; i < n; ++i) {
	  a[i] -= a[i - 1];
	}
	return 0;
}

