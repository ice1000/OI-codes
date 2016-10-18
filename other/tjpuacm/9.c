#include <stdio.h>

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))

int main(int argc, char *argv[]) {
  int i, j, k;
  scanf("%i %i %i", &i, &j, &k);
  printf("%i", __max(i, __max(j, k)) - __min(i, __min(j, k)));
  return 0;
}
