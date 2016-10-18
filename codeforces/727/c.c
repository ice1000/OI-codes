#include <stdio.h>

int a[1000001];

int main(int argc, char *argv[]) {
  int i, j, k, l, n, m;
  scanf("%i", &n);
  m = n;

  printf("? 1 2\n");
  fflush(stdout);
  scanf("%i", &i);

  printf("? 1 3\n");
  fflush(stdout);
  scanf("%i", &j);

  printf("? 3 2\n");
  fflush(stdout);
  scanf("%i", &k);

  l = (i + j + k) >> 1;

  a[1] = l - k;
  a[2] = l - j;
  a[3] = l - i;
  j = 4;

  while (j <= n) {
    printf("? 1 %i\n", j);
    fflush(stdout);
    scanf("%i", &k);
    a[j] = k - a[1];
    ++j;
  }
  printf("!");
  for (i = 1; i <= m; ++i) {
    printf(" %i", a[i]);
  }
  return 0;
}
/*
1 2 3 4 5 6 7 8
*/
