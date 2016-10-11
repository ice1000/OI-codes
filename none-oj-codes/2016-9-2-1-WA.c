#include <stdio.h>
#include <math.h>

typedef long long ll;
const int max = 120002;
ll pp[30000];
ll mm;
void fuck() {
	ll i, n, q;
	pp[mm++] = 2;
	for (n = 3; n < max; n += 2) {
		for (i = 0; i < mm; ++i)
			if (!(n % pp[i])) break;
		if (i >= mm) pp[mm++] = n;
	}
//	printf("%d\n", mm);
}

int main(int argc, char *argv[]) {
	ll n, i;
	ll a;
	fuck();
//	freopen("test", "r", stdin);
	scanf("%I64d", &n);
//	n = 4800;
	while (n--) {
		scanf("%I64d", &a);
		for (i = 0; i < mm; ++i)
			if (pp[i] * (ll) pp[i] == a) break;
		printf("%s\n", i >= mm ? "NO" : "YES");
	}
	return 0;
}
