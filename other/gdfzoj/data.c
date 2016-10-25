#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define n 10001

int main(int argc, const char *argv[]) {
  int i, j;
  freopen("in", "w", stdout);
  srand(time(0));
  printf("%i\n", n);
  for (i = 0; i < n; ++i) printf("%i ", abs(rand()));
  return 0;
}
/*
4
3 2 3 2
*/
