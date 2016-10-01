/*
作者:千里冰封
题目:p1220 数字三角形
*/

#include <stdio.h>

int n, dp[101][101];

int max(int x, int y) {
  return x > y ? x : y;
}

int main(int argc, char *argv[]) {
  int i, j;
  scanf("%i", &n);
  for (j = 0; j < n; ++j)
    for (i = 0; i <= j; ++i) {
      scanf("%i", &dp[j][i]);
    }

//  for (i = 0; i < n; ++i) dp[n - 1][i] = a[n - 1][i];

  for (i = n - 1; i >= 0; --i)
    for (j = 0; j <= i; ++j)
      dp[i][j] += max(dp[i + 1][j], dp[i + 1][j + 1]);

//  for (j = 0; j < n; ++j) {
//    for (i = 0; i <n; ++i) printf("%i ", dp[j][i]);
//    printf("\n");
//  }
  printf("%i", dp[0][0]);
  return 0;
}

/*
5
13
11 8
12 7 26
6 14 15 8
12 7 13 24 11
*/


