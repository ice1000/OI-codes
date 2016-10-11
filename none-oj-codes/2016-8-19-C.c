#include <stdio.h>
#include <math.h>

typedef long long ll;

ll n;
ll sum = -1;

int get(ll f) {
	int r = 0;
	while (f) r += f % 10, f /= 10;
	return r;
}

void shit(ll bitch, int i) {
	if (get(bitch) != i) return ;
	if (bitch * bitch + i * bitch != n) return ;
	if (sum == -1) sum = bitch;
	else if (sum > bitch) sum = bitch;
}

// x^2 + s(x) * x = n
int main(int argc, char* argv[]) {
	scanf("%I64d", &n);
	int i;
	ll d;
	for (i = 1; i <= 81; ++i) {
		d = (sqrt(i * i + 4 * n) - i) / 2;
		shit(d, i);
		shit(++d, i);
	}
	printf("%I64d", sum);
	return 0;
}

