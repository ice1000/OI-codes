#include<stdio.h>
#include<string.h>

#define size 25

typedef long long number;
int k;
number dp[size][size][size][size][size], num[size];

inline int check(number p1, number p2, number p3, number p4, number u) {
	switch (k) {
	case 2: return u != p4;
	case 3: return u != p4 && u != p3;
	case 4: return u != p4 && u != p3 && u != p2;
	default: return u != p4 && u != p3 && u != p2 && u != p1;
	}
}

number dfs(int pos, number p1, number p2, number p3, number p4, int flag) {
	if (!pos) return p4 != 10;
	if (!flag && ~dp[pos][p1][p2][p3][p4]) return dp[pos][p1][p2][p3][p4];
	number res = 0, u, ending = flag ? num[pos] : 9;
	for (u = 0; u <= ending; u++) {
		if (p4 == 10 && !u) res += dfs(pos - 1, 10, 10, 10, 10, flag && ending == u);
		else if (check(p1, p2, p3, p4, u)) res += dfs(pos - 1, p2, p3, p4, u, flag && ending == u);
	}
	if (!flag) dp[pos][p1][p2][p3][p4] = res;
	return res;
}

inline number solve(number x) {
	int len = 0;
	while (x) num[++len] = x % 10, x = x / 10;
	return dfs(len, 10, 10, 10, 10, 1);
}

int main() {
	freopen("num.in", "r", stdin);
	freopen("num.out", "w", stdout);
	number l, r;
	while (~scanf("%lli %lli %d", &l, &r, &k)) {
		memset(dp, -1, sizeof(dp));
		printf("%lli\n", solve(r) - solve(l - 1));

	}
}
