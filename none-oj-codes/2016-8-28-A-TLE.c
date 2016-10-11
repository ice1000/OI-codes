#include <stdio.h>

typedef long long ll;

ll fuck[5843] = {0, 1, 2, 3, 4};

const char* shit(int n) {
	if (n == 11 || n == 12) return "th";
	if (n % 10 == 1) return "st";
	if (n % 10 == 2) return "nd";
	return "th";
}

int main(int argc, char* argv[]) {
	int i;
	ll m, n;
	for (i = 5; i <= 5842; ++i) {
		m = fuck[i - 1];
		while (++m) {
			n = m;
			while (!(n % 7)) n /= 7;
			while (!(n % 5)) n /= 5;
			while (!(n % 3)) n /= 3;
			while (!(n & 1)) n >>= 1;
			if (n == 1) break;
		}
		printf("i = %d\n", i);
		fuck[i] = m;
	}
	while (1) {
		scanf("%d", &i);
		if (!i) break;
		printf("The %d%s humble number is %I64d.\n", i, shit(i), fuck[i]);
	}
	return 0;
}
