//
// Created by ice1000 on 2016/7/5.
//
#include <stdio.h>
#include <vector>
#include <memory.h>

using namespace std;

const int size = 1505;

vector<int> vec[size];

// dp[n][0] -> son
// dp[n][1] -> self
// dp[n][2] -> parent
int f[size], dp[size][3], n;

void init();

void dfs(int);

int main(int argc, char *argv[]) {
//	init();
	int i, j, k, l, m, a;
	while (scanf("%i", &n)) {
		memset(dp, 0, sizeof(dp));
		for (i = 0; i < n; i++) {
			scanf("%i:(%i) ", &j, &k);
			for (l = 0; l < k; l++) {
				scanf("%i", &a);
				vec[j].push_back(a);
				f[a]++;
			}
		}
		for (m = 0; m < n; ++m) {
			if(!f[m]) {
				dfs(m);
				printf("%i", max(1, 1));
			}
		}
	}
	return 0;
}

void dfs(int root) {
	for(int i = 0; i < vec[root].size(); i++) {
		int j = vec[root][i];
		dfs(j);
		dp[root][0] += min(dp[j][0], dp[j][1], dp[j][2]);
		dp[root][1] += min(dp[j][0], dp[j][1]);
		dp[root][2] += min(dp[j][0], dp[j][1]);
	}
	dp[root][0]++;
//	dp[root][1] += dp[]
}

void init() {
	freopen("soldier.in", "r", stdin);
	freopen("soldier.out", "w+", stdout);
}
