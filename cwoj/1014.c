// 双向链表写挂了，前来发泄一下心情

#include <stdio.h>

int n, mark[100], seq[100];

void dfs(int step) {
  int i;
  if (step >= n) {
    for (i = 1; i <= n; ++i) printf("%i ", seq[i]);
    putchar('\n');
  }
  ++step;
  for (i = 1; i <= n; ++i) {
    if (!mark[i]) {
      ++mark[i];
      seq[step] = i;
      dfs(step);
      --mark[i];
    }
  }
}

int main (int argc, char *argv[]) {
  scanf("%i", &n);
  dfs(0);
  return 0;
}

