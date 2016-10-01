#include <stdio.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int n, a[20], m[20], dp[20];

int main(int argc, char *argv[]) {
  int i, j, k = -1;

  scanf("%i", &n);

  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
  }

  for (i = 0; i < n; ++i) {
    dp[i] = 1;

    for (j = 0; j < i; ++j) {
      if (a[i] <= a[j])
	dp[i] = max(dp[i], dp[j] + 1);

      k = max(k, dp[i]);
    }
  }

  printf("%i", k);
}
