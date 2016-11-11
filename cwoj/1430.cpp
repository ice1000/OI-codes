// yzh lsw 机房发生X关系

#include <stdio.h>
#include <vector>

#define __size__ 100010

long long sum;
std::vector<int> vector[__size__];
int sz[__size__], s, n;

void dfs(int u, int par) {
	sz[u] = 1;
	size_t i;
	int v;
	for (i = 0; i < vector[u].size(); ++i) {
		v = vector[u][i];
		if (v == par) continue;
		dfs(v, u);
		sz[u] += sz[v];
	}
	s = n - sz[u];
	for (i = 0; i < vector[u].size(); ++i) {
		v = vector[u][i];
		if (v == par) continue;
		sum += 1ll * s * sz[v];
		s += sz[v];
	}
}

int main(int argc, const char *argv[]) {
	int i;
	int x, y;
	while (~scanf("%i", &n)) {
		for (i = 1; i <= n; ++i) vector[i].clear();
		for (i = 1; i < n; ++i) {
			scanf("%i %i", &x, &y);
			vector[x].push_back(y);
			vector[y].push_back(x);
		}
		sum = 0;
		dfs(1, -1);
		long long ans = 1ll * n * (n - 1) * (n - 2) / 6;
		printf("%lli\n", ans - sum);
	}
}
