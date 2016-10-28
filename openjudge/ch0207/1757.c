#include <stdio.h>

#define target 40

int a[1001], cnt, n;

void dfs(int idx, int value) {
	if (value >= target || idx >= n) {
		if (value == target) {
			++cnt;
		}
		return;
	}
	dfs(idx + 1, value + a[idx]);
	dfs(idx + 1, value);
}

int main(int argc, const char *argv[]) {
	int i, j;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
	  scanf("%i", &a[i]);
  }
  dfs(0, 0);
  printf("%i", cnt);
	return 0;
}
