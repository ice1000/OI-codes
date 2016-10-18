/*
  作者:千里冰封
  题目:p2602 最短路径问题
*/

#include <stdio.h>
#include <math.h>

double a[105][105];
int x[105], y[105];

int squared (int x) {
  return x * x;
}

double distance (int a, int b) {
  return sqrt(squared(x[a] - x[b]) + squared(y[a] - y[b]));
}

int main (int argc, char *argv[]) {
  int n, m, i, j, k;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j)
      a[i][j] = 0xfffff;
  for (i = 1; i <= n; ++i) scanf("%i %i", &x[i], &y[i]);
  scanf("%i", &m);
  for (i = 1; i <= m; ++i) {
    scanf("%i %i", &j, &k);
    a[k][j] = a[j][k] = distance(j, k);
  }
  /* Floyd */
  for (k = 1; k <= n; ++k)
    for (i = 1; i <= n; ++i)
      for (j = 1; j <= n; ++j)
	if (a[i][k] + a[k][j] < a[i][j]) a[i][j] = a[i][k] + a[k][j];
  scanf("%i %i", &i, &j);
  for (k = 1; k <= n; ++k) {
    printf("|%.2lf|", a[i][k]);
  }
  printf("%.2lf\n", a[i][j]);
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
