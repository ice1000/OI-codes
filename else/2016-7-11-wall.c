#include <stdio.h>

typedef long long LL;

LL dp[100005], n, a[100005], i, j;

LL max(LL x, LL y) {
	return x > y ? x : y;
}

LL min(LL x, LL y) {
	return x < y ? x : y;
}

int main(int argc, char* argv[]) {
	freopen("wall.in", "r", stdin);
	freopen("wall.out", "w+", stdout);
	scanf("%lli", &n);
	for(i = 0; i < n; i++) {
		scanf("%lli", &a[i]);
		LL to = 0, mn = 0xFFF;
		for(j = i - 1; j >= 0; j--) {
			to += a[j];
			mn = min(mn, a[j]);
			dp[i] = max(dp[i], to * mn);
		}
	}
	printf("%lli", dp[n - 1]);
	return 0;
}
