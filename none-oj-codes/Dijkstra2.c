#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define INF 0xffff

int a[1001][1001], d[1001], visit[1001];

int main(int argc, char *argv[]) {
  int m, n, i, j, x, y;
  scanf("%i %i", &n, &m);

  for (i = 0; i < n; ++i) {
    for (j = 0; j < n; ++j) {
      a[i][j] = INF;
    }
  }
  
  for (i = 0; i < m; ++i) {
    scanf("%i %i %i", &x, &y, &j);
    /* a[y][x] = j; */
    a[x][y] = j;
  }

  for (i = 0; i < n; ++i) {
    d[i] = a[1][i];
  }

  for (i = 1; i < n; ++i) {
    x = 0;
    for (j = 0; j < n; ++j) {
      if (!visit[j] && d[j] < d[x]) {
	x = j;
      }
    }
    ++visit[x];
    for (j = 0; j < n; ++j) {
      if (d[x] + a[x][j] < d[j]) {
	d[j] = d[x] + a[x][j];
      }
    }
  }
  return 0;
}
