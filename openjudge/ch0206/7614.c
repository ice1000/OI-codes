#include <stdio.h>

// 直接改了下2728的代码，太水了 

#ifdef __min
#undef __min
#endif

#define __min(x, y) ((x) < (y) ? (x) : (y))

int dp[1001][1001];

int main(int argc, char *argv[]) {
  int n, m, i, j, t;
  scanf("%i", &n);
  m = n;
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) {
      scanf("%i", &dp[i][j]);
    }
  }
  for (i = 1; i < n; ++i) {
    dp[i][0] += dp[i - 1][0];
  }
  for (j = 1; j < m; ++j) {
    dp[0][j] += dp[0][j - 1];
  }
  for (i = 1; i < n; ++i) {
    for (j = 1; j < m; ++j) {
      dp[i][j] += __min(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  printf("%i\n", dp[n - 1][m - 1]);
  return 0;
}
