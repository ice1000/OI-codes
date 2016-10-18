#include <stdio.h>

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))

int main(int argc, char *argv[]) {
  long long i, j, r;
  double a = 0.0;
  scanf("%lli", &j);
  r = __min(150000, j);
  for (i = 1; i <= r; ++i) {
    a += (1.0 / (i * i));
  }
  printf("%.5lf\n", a);
  return 0;
}

/*
5
1
2 3
4 5 6
10 1 7 8
1 1 4 5 6
*/
