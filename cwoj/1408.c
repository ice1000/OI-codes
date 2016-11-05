#include <stdio.h>

int a[20000010 << 1];

int main(int argc, const char *argv[]) {
  int n, i, j, k, m = 0;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i %i", &j, &k);
    if (j > k) {
      k ^= j;
      j ^= k;
      k ^= j;
    }
    if (k > m) m = k;
    ++a[j], --a[k + 1];
  }
  for (i = k = j = 0; i <= m; ++i) {
    k += a[i];
    if (k > j) j = k;
  }
  printf("%i", j);
}

