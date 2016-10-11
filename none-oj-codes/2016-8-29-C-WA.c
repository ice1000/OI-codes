#include <stdio.h>

const char *failed = "The times have changed\n";

char pair[105][105];
char mark[105];
int sequence[105];

int n, m, root = 1;

int dfs (int root, int index) {
	sequence[index++] = root;
	if (index >= n) return 1;
	int i;
	for (i = 1; i <= n; ++i) {
//		printf("pair[%d][%d] = %d, dump is %d\n", i, root, pair[i][root], pair[root][i]);
		if (!pair[i][root] && !mark[i]) {
			mark[i]++;
			if (dfs(i, index)) return 1;
		}
	}
	return 0;
}

int main (int argc, char *argv[]) {
	int i, j, k;
	long long y;
	scanf("%d %I64d %d", &n, &y, &m);
	if (y > 2500) {
		printf(failed);
		return 0;
	}
	for (i = 0; i < m; ++i) {
		scanf("%d %d", &j, &k);
		pair[j][k]++;
		if (pair[k][j]) {
			printf(failed);
			return 0;
		}
		if (k == root) root = j;
	}
	for (k = 1; k <= n; ++k)
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j)
				if (pair[i][k] && pair[k][j]) pair[i][j]++;
	mark[root]++;
	if (dfs(root, 0))
		for (i = 0; i < n; ++i) printf("%d ", sequence[i]);
	else {
		printf(failed);
		return 0;
	}
	return 0;
}

/**
3 2001 2 1 2 2 3

7 2020 6 1 2 1 3 2 4 2 5 3 6 3 7

3 2001 3 1 2 2 3 3 1
*/