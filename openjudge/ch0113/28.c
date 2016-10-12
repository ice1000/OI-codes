#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, j, n, a[502];
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i", &j);
    ++a[j + 201];
    if (a[j + 201] > (n >> 1)) {
      printf("%i", j);
      return 0;
    }
  }
  printf("no");
  return 0;
}