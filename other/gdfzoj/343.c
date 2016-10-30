#include <stdio.h>
#include <string.h>
#define size 1000005

int head[size], next[size], to[size], n, m;
int sz[size], ans[size];

int dfs(int now, int prev) {
  int i, tmp;
  for (i = head[now]; ~i; i = next[i]) {
    if (to[i] == prev) continue;
    tmp = dfs(to[i], now);
    sz[now] += tmp;
    if (tmp > ans[now]) ans[now] = tmp;
  }
  tmp = n - sz[now] - 1;
  if (tmp > ans[now]) ans[now] = tmp;
  return sz[now] + 1;
}

int main(int argc, const char *argv[]) {
  int i, j, k, l;
  memset(head, -1, sizeof(head));
  memset(next, -1, sizeof(next));
  scanf("%i", &n);
  for (i = 1; i <= ((n - 1) << 1); i += 2) {
    scanf("%i %i", &j, &k);
    to[i] = j;     next[i] = head[k];     head[k] = i;
    to[i + 1] = k; next[i + 1] = head[j]; head[j] = i + 1;
  }
  dfs(1, 0);
  l = 0xfffff;
  for (i = 1; i <= n; ++i) {
    if (l > ans[i]) {
      l = ans[i];
    }
  }
  printf("%i", l);
  return 0;
}

/*
5
1 2
1 3
4 3
5 1
*/

