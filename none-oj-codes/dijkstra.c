/*
 * 《啊哈算法》Dijkstra练习
 * 这太暴力了
 */

#include <stdio.h>
#include <stdlib.h>

const int MAX = 0xffffff, NODE_SIZE = 100, EDGE_SIZE = 100;
int a[NODE_SIZE], edge[EDGE_SIZE][EDGE_SIZE], b[NODE_SIZE];

int main(int argc, char* argv[]) {
  int i, j, k, l, n, m;
  scanf("%i %i", &n, &m);
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j)
      edge[i][j] = i - j ? MAX : 0;
  for (i = 1; i <= n; ++i) {
    scanf("%i %i %i", &j, &k, &l);
    edge[j][k] = l;
  }
  for (i = 1; i <= m; ++i) {
    a[i] = edge[1][i];
    b[i] = 0;
  }
  ++b[1];
  for (i = 1; i <= n - 1; ++i) {
    k = MAX;
    for (j = 1; j <= n; ++j) {
      if (!b[j] && a[j] < k) {
	k = a[j];
	l = j;
      }
    }
    ++b[l];
    for (j = 1; j <= n; ++j) {
      if (edge[l][j] < MAX && a[j] > a[l] + edge[l][j]) {
	a[j] = a[l] + edge[l][j];
      }
    }
  }
  for (i = 1; i <= n; ++i)
    printf("%i ", a[i]);
  return 0;
}
