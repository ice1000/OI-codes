#include <stdio.h>

int map[101][101];
int dp[101][101];

int main(int argc, char *argv[]) {
  int n, i, j, a, b, m = -1, k;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j) {
      scanf("%i", &map[i][j]);
    }
  for (i = 1; i <= n; ++i)
    for (j = 1; j <= n; ++j) {
      dp[i][j] = map[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
    }
  // 听说n4的暴力能过，数据很水
  for (a = 1; a <= n; ++a)
    for (b = 1; b <= n; ++b)
      for (i = 0; i <= a; ++i)
	for (j = 0; j <= b; ++j) {
	  k = dp[a][b] - dp[a][j] - dp[i][b] + dp[i][j];
	  if (k > m) m = k;
	}
  printf("%i", m);
  return 0;
}

/**
4 0 -2 -7 0 9 2 -6 2 -4 1 -4 1 -1 8 0 -2
*/
