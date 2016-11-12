#include <stdio.h>
#include <string.h>

#define init(x, y) (memset(x, y, sizeof(x)))
#define true 1
#define false 0

typedef long long number;

number n, m, k;
int map[10];

inline number in() {
	number x = 0, ch;
	do ch = getchar(); while (ch < '0' || ch > '9');
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int judge(number num) {
	init(map, 0);
	number i = 1, j = 1;
	while (num / i) {
		if (map[(num / i) % 10]) return false;
		++map[(num / i) % 10];
		if (i >= k) {
			--map[(num / j) % 10];
			j *= 10;
		}
		i *= 10;
	}
	return true;
}

int main(int argc, const char *argv[]) {
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	number i, j = 0;
	n = in();
	m = in();
	k = in();
	for (i = n; i <= m; ++i) {
		if (judge(i)) ++j;
//		printf("%llu\n", i);
	}
	printf("%lli", j);
	return 0;
}

