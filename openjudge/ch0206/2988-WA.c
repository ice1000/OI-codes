#include <stdio.h>
#include <string.h>

#ifndef __max
#define __max(x, y) ((x) > (y) ? (x) : (y))
#endif

char a[1001], b[1001], dp[1001][1001];

int main(int argc, char *argv[]) {
  int t, i, j, k;
  scanf("%i", &t);
  while (t--) {
    scanf("%s %s", a, b);
    i = j = 0;
    memset(dp, 0, sizeof(dp));
    for (i = 0; i < strlen(a); ++i) {
      for (j = 0; j < strlen(b); ++j) {
        if (a[i] == b[j] && dp[i - 1][j - 1] + 1 > dp[i][j]) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = __max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    printf("%i\n", __max(strlen(a), strlen(b)) - dp[strlen(a) - 1][strlen(b) - 1]);
  }
  return 0;
}

/*
3
abcdefg  abcdef
ab ab
mnklj jlknm
*/

