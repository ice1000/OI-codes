/*
  作者:千里冰封
  题目:p1017 乘积最大
*/

#include <stdio.h>

// dp[i][j][kk] = max{dp[i][m][left]*dp[m+1][j][kk-left-1]}

#define int long long
#define __max(x, y) ((x) > (y) ? (x) : (y))

int n, k, a[101], dp[101][101][101];

#undef int
int main(int argc, char *argv[]) {
#define int long long
  int i, j, l, max = -1, mx, b, c, m;
  scanf("%lli %lli %s", &n, &k, a);
  for (i = 0; i < n; ++i) {
  	dp[i][i][0] = a[i] - '0';
  	for (j = i + 1; j < n; ++j) {
	  dp[i][j][0] = dp[i][j - 1][0] * 10 + a[j] - '0';
  	}
  }
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      for (l = 0; l < k; ++l) {
		mx = 0;
    	for (b = i; b <= j; ++b) {
		  for (c = 0; c < l; ++c) {
		    mx = __max(dp[i][b][c] * dp[b][j][l - c - 1], mx);
		  }
		}
		dp[i][j][l] = mx;
		max = __max(mx, max);
      }
    }
  }
  printf("%lld\n", max);
  return 0;
}

