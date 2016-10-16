/*
作者:千里冰封
题目:p2602 最短路径问题
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define INF 0xffffff

double a[105][105], d[105];
int x[105], y[105], v[105];

int squared (int x) {
  return x * x;
}

double distance (int a, int b) {
  return sqrt(squared(x[a] - x[b]) + squared(y[a] - y[b]));
}

int main (int argc, char *argv[]) {
  int n, m, i, j, k, l, o;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) {
    for (j = 1; j <= n; ++j) {
      a[i][j] = INF;
    }
  }
  for (i = 1; i <= n; ++i) {
    scanf("%i %i", &x[i], &y[i]);
  }
  scanf("%i", &m);
  for (i = 1; i <= m; ++i) {
    scanf("%i %i", &j, &k);
    a[k][j] = a[j][k] = distance(j, k);
  }
	/* Dijkstra */
  scanf("%i", &i);
  for (j = 1; j <= n; ++j) {
    d[j] = a[i][j];
    v[j] = 0;
  }
  /* d = a[i]; */
  j = n;

  while (j--) {
    o = 1;
    for (k = 1; k <= n; ++k) {
     if (!v[k] && d[k] < d[o]) {
       o = k;
     }
     ++v[o];
     for (k = 1; k <= n; ++k) {
       if (d[o] + a[o][k] < d[k]) {
         d[k] = d[o] + a[o][k];
       }
     }
    }
  }
  for (j = 1; j <= n; ++j) {
  	printf("|%.2lf|", d[j]);
  }
  scanf("%i", &i);
  printf("%.2lf\n", d[i]);
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

