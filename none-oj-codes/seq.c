#include <stdio.h>

int a[100001], dp[100001];

int find(int l, int r, int n) {
  if (l >= r) return l;
  int mid = (l + r) / 2;
  return dp[mid] == n ? mid : dp[mid] > n ? find(l, mid, n) : find(mid + 1, r, n);
}

int main(int argc, char *argv[]) {
  freopen("seq.in", "r", stdin);
  freopen("seq.out", "w", stdout);
  int i, j, n, d, max;
  while (scanf("%i %i", &n, &d) != EOF) {
    for (i = 0; i < n; ++i) {
      scanf("%i", &a[i]);
      dp[i] = 1;
    }
    max = 1;
    for (i = 0; i < n; ++i) {
//      if (a[i] - dp[m] > d) dp[++m] = a[i];
//      else dp[find(0, m, a[i])] = a[i];
      for (j = 0; j <= i; ++j) {
        if (a[i] - a[j] > d && dp[i] + 1 > dp[j]) {
          dp[j] = dp[j] + 1;
          if (dp[j] > max) {
           max = dp[j];
          }
        }
      }
    }
    printf("%i\n", max);
  }
  return 0;
}

/*
2 0
1 2
5 1
3 4 5 1 2
5 2
3 4 5 1 2
*/
