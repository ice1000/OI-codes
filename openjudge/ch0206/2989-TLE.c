#include <stdio.h>

int a[1001], n, k, max = 0;

void dfs(int idx, int cur) {
  if (idx >= n) {
    if (!(cur % k) && cur > max) {
      max = cur;
    }
    return;
  }
  dfs(idx + 1, cur);
  dfs(idx + 1, cur + a[idx]);
}

int main(int argc, char *argv[]) {
  int i, j;
  scanf("%i %i", &n, &k);
  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
  }
  dfs(0, 0);
  printf("%i", max);
  return 0;
}

/*
5 7
1
2
3
4
5
*/

