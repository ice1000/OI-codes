#include <stdio.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))

int dp[1001][1001];

int main(int argc, char *argv[]) {
  int n, m, i, j, max = 0;
  scanf("%i %i", &n, &m);
  for (i = 0; i < __max(n, m); ++i) dp[i][0] = dp[0][i] = 1;
  for (i = 1; i < n; ++i) {
    for (j = 1; j < m; ++j) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  }
  printf("%i", dp[n - 1][m - 1]);
  return 0;
}

/*
8
186 186 150 200 160 130 197 220
*/

