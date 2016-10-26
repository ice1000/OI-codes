#include <stdio.h>
#define mod 23323323233

int a[10005], ans[1000005], ans_idx;

int main(int argc, const char *argv[]) {
  int n, m, i, j;
  long long ret, tmp;
  scanf("%i %i", &n, &m);
  for (i = 0; i <= n; ++i) {
    scanf("%i", &a[i]);
  }
  for (i = 1; i <= m; ++i) {
    ret = 0;
    tmp = 1;
    for (j = 0; j <= n; ++j) {
      ret = (ret + tmp * a[j]) % mod;
      tmp = tmp * i % mod;
    }
    if (!ret) ans[ans_idx++] = i;
  }
  printf("%i\n", ans_idx);
  for (i = 0; i < ans_idx; ++i) {
    printf("%i\n", ans[i]);
  }
  return 0;
}
