#include <stdio.h>

int dp[105] = {1, 1, 2};

int main(int argc, char *argv[]) {
  int n = 100, i, j;
  for (i = 3; i <= n; ++i) dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
  while (1) {
    scanf("%i", &n);
    if (!n) break;
    printf("%i\n", dp[n]);
  }
  return 0;
}
