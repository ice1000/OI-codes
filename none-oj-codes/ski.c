#include <math.h> 
#include <stdio.h>
#include <string.h>

const int mod = 1e9 + 7;
const int move[][2] = {
	{  1, 0 },
	{ -1, 0 },
	{  0, 1 },
	{ 0, -1 }
};

int n, m, k, a[110][110];
int ans[100010 << 1], ans_idx, out;

void dfs(int x, int y, int l = 1) {
	ans[ans_idx++] = l++;
	int i, j, k = 4;
	while (k --> 0) {
		i = x + move[k][0];
		j = y + move[k][1];
		if (a[i][j] < a[x][y]) {
			dfs(i, j, l);
		}
	}
}

int main(int argc, const char *argv[]) {
  freopen("ski.in", "r", stdin);
  freopen("ski.out", "w", stdout);
	int i, j;
	// n = 30;
	// m = 30;
	scanf("%i %i %i", &n, &m, &k);
	memset(a, 0x7f, sizeof(a));
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			// printf("%i ", a[i][j]);
			scanf("%i", &a[i][j]);
		}
	}
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			dfs(i, j);
		}
	}
	printf("%i\n", ans_idx);
	for (i = 0; i < ans_idx; ++i) {
		out = (out + ans[i]) % mod;
	}
	printf("%i", out);
	if (k > 1) {
	  for (j = 2; j <= k; ++j) {
  		for (i = 0; i < ans_idx; ++i) {
  			out = (out + ans[i]) % mod;
  		}
  		printf("%i", out);
    }
	}
	return 0;
}
