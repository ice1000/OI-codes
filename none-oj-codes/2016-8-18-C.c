#include <stdio.h>

char fuck[101][1001];
int bitch[101];
int shit[1001][1001];
int total[1001];
int n, k, m;

void dfs(int cow, int begin) {
	int i;
	fuck[cow][begin]++;
	total[begin]++;
	for (i = 1; i <= n; ++i)
		if (!fuck[cow][i] && shit[begin][i]) dfs(cow, i);
}

int main(int argc, char* argv[]) {
	int i, j, a, b, c = 0;
	scanf("%d %d %d", &k, &n, &m);
	for (i = 1; i <= k; ++i) {
		scanf("%d", &j);
//		++fuck[i][j];
		bitch[i] = j;
	}
	for (i = 1; i <= m; ++i) {
		scanf("%d %d", &a, &b);
		shit[a][b]++;
	}
	for (i = 1; i <= k; ++i) if (bitch[i]) dfs(i, bitch[i]);
	for (i = 1; i <= n; i++) if (total[i] >= k) c++;
//	for (i = 1; i <= n; i++)
	printf("%d", c);
	return 0;
}

/*
2 4 4 2 3 1 2 1 4 2 3 3 4

*/
