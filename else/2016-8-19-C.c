#include <stdio.h>
#include <math.h>

typedef long long ll;

ll n, min;

void find(ll l, ll r) {
	if (l > r) return;
	ll mid = (l + r) / 2;
}

// x^2 + s(x) * x = n
int main(int argc, char* argv[]) {
	scanf("%I64d", &n);
	find(1, sqrt(n));
	return 0;
}

