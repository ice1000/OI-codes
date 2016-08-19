#include <stdio.h>
#include <math.h>

typedef long long ll;

ll n, min;

ll s(ll a) {
	ll r = 0;
	while (a) r += a % 10, a /= 10;
	return r;
}

void find(ll l, ll r) {
	if (l > r) return;
	ll mid = (l + r) / 2;
	ll fuck = mid * mid + s(mid) * mid;
	if (fuck > n) find(l, mid);
	else if (fuck < n) find(mid + 1, r);
	else min = fuck;
}

// x^2 + s(x) * x = n
int main(int argc, char* argv[]) {
	scanf("%I64d", &n);
	find(1, sqrt(n));
	printf("%d", min);
	return 0;
}

