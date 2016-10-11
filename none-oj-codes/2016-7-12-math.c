#include <stdio.h>

typedef long long ll;

ll fast_pow(ll a, ll b) {
	ll ret = 1, x = 2;
	while(a) {
		if(a & 1)
			ret = (ret * x) % b;
		x = (x * x) % b;
		a >>= 1;
	}
	return ret;
}

int main(int argc, char* argv[]) {
	freopen("math.in", "r", stdin);
	freopen("math.out", "w+", stdout);
	ll x, y;
	scanf("%lli %lli", &x, &y);
	printf("%lli", fast_pow(x, y));
	return 0;
}
