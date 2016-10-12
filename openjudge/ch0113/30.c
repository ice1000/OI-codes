#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, j = 0, n;
  scanf("%i", &n);
  for (i = 0; n; ++i) {
    if (n & 1)
      ++j;
    n >>= 1;
  }
  printf("%i", j);
  return 0;
}
