#include <stdio.h>

int seq[1001];
int dp[1001] = {-1};

int find(int l, int r, int n) {
  if (l >= r) return l;
  int mid = (l + r) >> 1;
  return dp[mid] == n ? mid : dp[mid] > n ? find(l, mid, n) : find(mid + 1, r, n);
}

int main(int argc, char *argv[]) {
  int n, i, j, len = 0;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) scanf("%i", &seq[i]);
  for (i = 0; i < n; ++i) {
    if (seq[i] > dp[len]) j = ++len;
    else j = find(0, len, seq[i]);
    dp[j] = seq[i];
  }
  printf("%i", len);
  return 0;
}

