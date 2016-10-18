/*
  作者:千里冰封
  题目:p2602 最短路径问题
*/

#include <stdio.h>
#include <math.h>

#define INF 0xfffff
#define squared(x) ((x) * (x))

struct {
  int u, v;
  double w;
} edge[1001];

int x[105], y[105];
double d[105];

double distance (int a, int b) {
  return sqrt(squared(x[a] - x[b]) + squared(y[a] - y[b]));
}

int main (int argc, char *argv[]) {
  int n, m, i, j, k, fr, en;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) scanf("%i %i", &x[i], &y[i]);

  scanf("%i", &m);

  for (i = 1; i <= m; ++i) {
    scanf("%i %i", &j, &k);
    edge[i].u = k;
    edge[i].v = j;
    edge[i].w = distance(j, k);
  }

  scanf("%i %i", &fr, &en);

  for (i = 1; i <= n; ++i) {
    d[i] = i == fr ? 0 : INF;
  }

  /* Bellman-Ford */
  for (k = 1; k < n; ++k) {
    for (i = 1; i <= m; ++i) {
      if (d[edge[i].v] > d[edge[i].u] + edge[i].w) {
        d[edge[i].v] = d[edge[i].u] + edge[i].w;
      }
      if (d[edge[i].u] > d[edge[i].v] + edge[i].w) {
        d[edge[i].u] = d[edge[i].v] + edge[i].w;
      }
    }
  }

  /* for (k = 1; k <= n; ++k) { */
  /*   printf("|%.2lf|", a[i][k]); */
  /* } */
  printf("%.2lf\n", d[en]);
  return 0;
}

/*
5
0 0
2 0
2 2
0 2
3 1
5
1 2
1 3
1 4
2 5
3 5
1 5
*/
