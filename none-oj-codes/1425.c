#include <stdio.h>

#define BIG 0xffff

#ifdef __min(x, y)
#undef __min(x, y)
#define __min(x, y) ((x) < (y) ? (x) : (y))

int n, tt, dp[301][101], a[101], t[101];
int m1[101], m1n, m2[101], m2n;
int ht1[301][101], ht2[301][101];

int main(int argc, char *argv[]) {
  int i, j, k, fuck = 0;
  while (1) {
    scanf("%i", &n);
    if (!n) break;
    scanf("%i", &tt);
    for (i = 1; i <= n - 1; ++i) {
      scanf("%i", &a[i]);
      dp[tt][i] = BIG;
    }
    dp[tt][n] = 0;
    scanf("%i", &m1n);
    for (i = 1; i <= m1n; ++i) {
      scanf("%i", &m1[i]);
      // 在j时刻，k车站是否有向左的列车
      for (k = 1, j = m1[i]; j <= tt; j += a[k], ++k) {
	ht1[j][k]++;
      }
    }
    scanf("%i", &m2n);
    for (i = 1; i <= m2n; ++i) {
      scanf("%i", &m2[i]);
      // 在j时刻，k车站是否有向右的列车
      for (k = 1, j = m2[i]; j <= tt; j += a[k], ++k) {
	ht2[j][k]++;
      }
    }

    for (i = tt - 1; i ; --i) {
      for (j = 1; j <= n; ++j) {
	dp[i][j] = dp[i + 1][j] + 1;
	if (j < n && ht1[i][j] && i + t[j] <= tt)
	  dp[i][j] = __min(dp[i][j], dp[i + t[j]][j + 1]);
	if (j > 1 && ht2[i][j] && i + t[j - 1] <= tt)
	  dp[i][j] = __min(dp[i][j], dp[i - t[j - 1]][j - 1]);
      }
    }
    
    ++fuck;
    printf("Case Number %i: ", fuck);
    if (dp[0][1] >= BIG) printf("impossible\n");
    else printf("%i\n", dp[0][1]);
  }
  return 0;
}
