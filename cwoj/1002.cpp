#include <stdio.h>
#include <string.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))

int a[1001];
int dp1[1001] = { 1 };
int dp2[1001] = { 1 };

int main(int argc, char *argv[]) {
  int n, i, j, max = 0;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
    dp1[i] = dp2[i] = 1;
  }
  for (i = 1; i < n; ++i) {
    for (j = 0; j < i; ++j) {
      if (a[i] > a[j])
        dp1[i] = __max(dp1[j] + 1, dp1[i]);
    }
  }
  for (i = n - 2; i >= 0; --i) {
    for (j = n - 1; j > i; --j) {
      if (a[i] > a[j])
        dp2[i] = __max(dp2[j] + 1, dp2[i]);
    }
  }
  for (i = 0; i < n; ++i) {
    max = __max(max, dp1[i] + dp2[i]);
  }
  printf("%i", n - max + 1);
  return 0;
}

