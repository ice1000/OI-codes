#include <stdio.h>

char a[2050];

int main(int argc, const char *argv[]) {
  int i, j, n, m;
  scanf("%d %s", &n, a);
  for (i = 0; i < n; ++i)
    for (j = 0; j * n < strlen(a); ++j)
      putchar(j & 1 ? a[(j + 1) * n - i - 1] : a[j * n + i]);
  return 0;
}

