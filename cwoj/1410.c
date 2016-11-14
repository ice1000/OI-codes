#include <stdio.h>

#define Ha 12345678

int shit[500010] = { 1 };

int main(int argc, const char *argv[]) {
  int n, i, j, k, l = 0, ans = 0;
  scanf("%i %i", &n, &k);
  for (i = 0; i < n; ++i) {
    scanf("%i", &j);
    l = (l + j) % k;
    ++shit[l];
  }
  for (i = 0; i <= k; ++i) {
    ans += shit[i] * (shit[i] - 1) / 2;
  }
  printf("%i", ans % Ha);
  return 0;
}

