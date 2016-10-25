#include <stdio.h>

int a[1001];

int main(int argc, const char *argv[]) {
  int i, j, n, m;
  scanf("%i %i", &n, &m);
  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
    for (j = 0; j < i; ++j) {
      if (a[i] + a[j] == m) {
        puts("yes");
        return 0;
      }
    }
  }
  puts("no");
  return 0;
}
