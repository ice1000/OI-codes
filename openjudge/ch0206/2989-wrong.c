#include <stdio.h>

int a[1001], mark[1001];
int n, k, max = 0;

void dfs(int idx, int cur) {
  if (idx <= 0) return;
  int i;
  for (i = 0; i < n; ++i) {
    if (!mark[i]) {
      ++mark[i];
      cur -= a[i];
      if (!(cur % k) && cur > max) {
        max = cur;
      }
      dfs(idx - 1, cur);
      --mark[i];
      cur += a[i];
    }
  }
  if (max) {
    return;
  }
}

int main(int argc, char *argv[]) {
  int i, j, tot = 0;
  scanf("%i %i", &n, &k);
  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
    tot += a[i];
  }
  dfs(0, tot);
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

