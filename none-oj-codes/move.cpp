#include <bits/stdc++.h>

#define __abs(x) (x) > 0 ? (x) : (-(x))

long long a[5000005], sum_avg, res;

int main(int argc, char *argv[]) {
	freopen("move.in", "r", stdin);
	freopen("move.out", "w", stdout);
	int n, i, j;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		std::cin >> a[i];
		sum_avg += a[i];
	}
	sum_avg /= n;
	for (i = 0; i < n; ++i) res += __abs(a[i] - sum_avg);
	std::cout << res / 2 << std::endl;
	return 0;
}
/*5 17 9 14 16 4*/
