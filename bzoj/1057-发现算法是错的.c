// 卧槽啊我发现算法是错的
#include <stdio.h>

int a[2001][2001], n, m, b[2001][2001], l[2001][2001], r[2001][2001];

int main(int argc, char *argv[]) {
  int i, j, max = -1, max2 = -1;
  scanf("%i %i", &n, &m);
  for (i = 0; i < n; ++i)
    for (j = 0; j < m; ++j) {
      scanf("%i", &a[i][j]), b[i][j] = 0;
    }
  // i是纵坐标，j是横坐标
  for (i = 0; i < m; ++i) {
    b[0][i] = 1;
    for (j = 1; j < n; ++j) b[j][i] = a[j][i] ^ a[j - 1][i] ? b[j - 1][i] + 1 : 1;
  }
  // i是横坐标，j是纵坐标
  for (i = 0; i < n; ++i) {
    l[i][0] = 1;
    for (j = 1; j < m; ++j) l[i][j] = a[i][j] ^ a[i][j - 1] ? l[i][j - 1] + 1 : 1;
    r[i][m - 1] = 1;
    for (j = m - 2; j >= 0; --j) r[i][j] = a[i][j] ^ a[i][j + 1] ? r[i][j + 1] + 1 : 1;
  }
  printf("\n");
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) printf("%i ", b[i][j]);
    printf("\n");
  }
  printf("\n");
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) printf("%i ", l[i][j]);
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
      if (b[i][j] == l[i][j] and b[i][j] * l[i][j] > max2) max2 = b[i][j] * l[i][j];
      if (b[i][j] * r[i][j] > max) max = b[i][j] * r[i][j];
      if (b[i][j] == r[i][j] and b[i][j] * r[i][j] > max2) max2 = b[i][j] * r[i][j];
    }
  printf("%i\n%i", max2, max);
  return 0;
}
/**
3 4
1 0 1 0
0 0 0 0
1 0 1 0
*/

