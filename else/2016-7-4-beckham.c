#include <stdio.h>

void init() {
	freopen("beckham.in", "r", stdin);
	freopen("beckham.out", "w+", stdout);
}

const int size = 5005;

typedef struct {
	int v;
	int w;
} ITEM ;

int n, v, dp[size];
ITEM a[size];

int max(int x, int y) {
	return x > y ? x : y;
}

int dp_run() {
	int i, j;
	for(i = 1; i <= n; i++)
		for(j = v; j >= a[i].w; j--)
			dp[j] = max(dp[j], dp[j - a[i].w] + a[i].v);
	return dp[++j];
}

int main(int argc, char *argv[]) {
	init();
	int i;
	scanf("%d%d", &n, &v);
	for(i = 1; i <= n; i++)
		scanf("%d%d", &a[i].w, &a[i].v);
	printf("%d", dp_run());
	return 0;
}
