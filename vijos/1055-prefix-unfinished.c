#include <stdio.h>

int a[2001][2001], n, m;
// 二维前缀和复杂度太高了
int main(int argc, char *argv[]) {
  int i, j, max = -1, t;
  scanf("%i %i %i", &n, &m, &t);

  while (t--) {
    scanf("%i %i", &i, &j);
    ++a[i][j];
  }
  for (i = 1; i < n; ++i) {
    for (j = 1; j < m; ++j) {
      a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
  }

  printf("%i", max);
  return 0;
}
/**
10 10
4
1 1
9 1
1 9
9 9
*/
