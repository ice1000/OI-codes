#include <stdio.h>
#include <string.h>

int max(int x, int y) {
  return x > y ? x : y;
}

int dp[202][202], n, m;
char a[202], b[202];

int main(int argc, char *argv[]) {
  int i, j;
  while (scanf("%s %s", a + 1, b + 1) != EOF) {
    n = strlen(a + 1);
    m = strlen(b + 1);
    memset(dp, 0, 202 * 202 * sizeof(int));
    for (i = 1; i <= n; ++i)
      for (j = 1; j <= m; ++j) {
	if (a[i] == b[j] &&
	    dp[i - 1][j - 1] + 1 > dp[i][j])
	  dp[i][j] = dp[i - 1][j - 1] + 1;
	else
	  dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    printf("%i\n", dp[n][m]);
  }
  return 0;
}
/**
   abcfbc         abfcab
   programming    contest
   abcd           mnp

*/
