#include <stdio.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))

int dp[1001][1001];

int main(int argc, char *argv[]) {
  int n, m, i, j, max = 0, t;
  scanf("%i", &t);
  while (t--) {
    scanf("%i %i", &n, &m);
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
        dp[i][j] += __max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
    printf("%i\n", dp[n - 1][m - 1]);
  }
  return 0;
}

/*
2
2 2
1 1
3 4
2 3
2 3 4
1 6 5
*/

