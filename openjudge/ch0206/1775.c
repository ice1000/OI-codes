#include <stdio.h>
#define __max(x, y) ((x) > (y) ? (x) : (y))

int w[101], v[101], dp[1001];

int main(int argc, char *argv[]) {
  int m, t, i, j, n = -1;
  scanf("%i %i", &t, &m);
  for (i = 0; i < m; ++i) scanf("%i %i", &w[i], &v[i]);
  for (i = 0; i < m; ++i)
    for (j = t; j >= w[i]; --j) {
      dp[j] = __max(dp[j], dp[j - w[i]] + v[i]);
      if (dp[j] > n) n = dp[j];
    }
  printf("%i", n);
  return 0;
}

/**
70 3 71 100 69 1 1 2
*/
