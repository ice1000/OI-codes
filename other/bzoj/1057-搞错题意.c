#include <stdio.h>
#define _BIG_ 0xffff
#define _SMALL_ -0xffff
int a[2001][2001], n, m, b[2001][2001], l[2001][2001], r[2001][2001];

int main(int argc, char *argv[]) {
  int i, j, max = -1, max2 = -1;
  scanf("%i %i", &n, &m);
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j) {
      scanf("%i", &a[i][j]);
      b[i][j] = _SMALL_;
    }
  // i是纵坐标，j是横坐标
  for (i = 0; i < m; ++i) {
    b[0][i] = a[0][i] ? 0 : 1;
    for (j = 1; j < n; ++j)
      b[j][i] = !a[j][i] ? b[j - 1][i] + 1 : 0;
  }
  // i是横坐标，j是纵坐标
  for (i = 0; i < n; ++i) {
    l[i][0] = a[i][0] ? 0 : 1;
    for (j = 1; j < m; ++j)
      l[i][j] = !a[i][j - 1] ? l[i][j - 1] + 1 : 0;
    r[i][m - 1] = a[i][m - 1];
    for (j = m - 1; j >= 0; --j)
      r[i][j] = !a[i][j + 1] ? r[i][j + 1] + 1 : 0;
  }
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j)
      printf("%i ", l[i][j]);
    printf("\n");
  }
  printf("\n");
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j)
      printf("%i ", r[i][j]);
    printf("\n");
  }

  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j) {
      if (b[i][j] * l[i][j] > max) max = b[i][j] * l[i][j];
      if (b[i][j] * r[i][j] > max) max = b[i][j] * r[i][j];
      if (i == j) max2 = max;
    }
  printf("%i\n%i", max2, max);
  return 0;
}
/**
3 3
1 0 1
0 1 0
1 0 0
*/
