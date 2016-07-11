#include <stdio.h>

int main(int argc, char* argv[]) {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w+", stdout);
	int n, o, i, p;
	scanf("%i", &n);
	for(i = 1; i <= n; i++) {
		long long a, b;
		o = 0, p = 0;
		scanf("%lli %lli", &a, &b);
		while(a > b) {
			p++;
			a -= a / 2;
			if(!(a % 2)) a++;
		}
		printf("Case %i: %i", i, p);
	}
	return 0;
}
