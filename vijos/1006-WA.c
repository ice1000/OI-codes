#include <stdio.h>

#ifdef __min
#undef __min
#endif

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))

int n, a[1001][1001], dp[1001][1001];

void outputCache() {
  int i, j;
  for (i = n - 1; i >= 0; --i) {
    for (j = 0; j <= n - i - 1; ++j)
      printf("%i ", dp[i][j]);
    puts("");
  }
  puts("");  
} 

int main(int argc, char *argv[]) {
  freopen("in.exe", "r", stdin);
  int i, j;
  scanf("%i", &n);

  for (i = n - 1; i >= 0; --i)
    for (j = 0; j <= n - i - 1; ++j)
      scanf("%i", &a[i][j]);

  dp[0][0] = a[0][0];

  for (j = 1; j < n; ++j)
    dp[0][j] = dp[0][j - 1] + a[0][j];

  dp[0][n - 1] = __min(dp[0][n - 1], dp[0][0] + a[0][n - 1]);

  for (j = n - 2; j >= 0; --j)
    dp[0][j] = __min(dp[0][j], dp[0][j + 1] + a[0][j]);

  for (i = 1; i < n; ++i) {
//    outputCache();
    dp[i][0] = __min(dp[i - 1][0], dp[i - 1][1]) + a[i][0];

    dp[i][0] = __min(dp[i - 1][n - i] + a[i][0], dp[i][0]);

    for (j = 1; j < n - i; ++j) {
      dp[i][j] = __min(dp[i][j - 1],
                       __min(
	                           dp[i - 1][j],
                             dp[i - 1][j + 1])
                       ) + a[i][j];
    }

    dp[i][n - i - 1] = __min(dp[i][n - i - 1], dp[i - 1][0] + a[i][n - i - 1]);
    dp[i][n - i - 1] = __min(dp[i][n - i - 1], dp[i][0] + a[i][n - i - 1]);
    dp[i][0] = __min(dp[i][n - i - 1] + a[i][0], dp[i][0]);

    for (j = n - i - 2; j > 0; --j) {
      dp[i][j] = __min(dp[i][j + 1],
                       __min(
                             dp[i - 1][j],
                             dp[i - 1][j + 1])
                       ) + a[i][j];
    }
  }
  printf("%i", dp[n - 1][0]);
  return 0;
}

/*
5
    1
   1 1
  1 1 1
 8 1 1 1
1 1 1 1 1
*/
