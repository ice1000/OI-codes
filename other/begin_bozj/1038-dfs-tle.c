#include <stdio.h>

int ans;

void dfs(int cost) {
	if (cost > 100) return;
	if (cost == 100) {
		++ans;
		return;
	}
	dfs(cost + 1);
	dfs(cost + 2);
	dfs(cost + 5);
}

int main(int argc, const char *argv[]) {
  dfs(8);
	printf("%i", ans);
	return 0;
}

