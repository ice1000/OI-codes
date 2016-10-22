#include <stdio.h>

char a[400001];

int main(int argc, char *argv[]) {
  int i, j, n;
  scanf("%i", &n);
  getchar();
  for (i = 0; i < n; ++i) {
    a[i] = getchar();
  }
  i = 0;
  while (a[i] == '<') ++i;
  j = n - 1;
  while (a[j] == '>') --j;
//  printf("%i %i\n", i, j);
  printf("%i", n - j + i - 1);
  return 0;
}
/*
4
<<><
*/
