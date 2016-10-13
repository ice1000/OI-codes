#include <stdio.h>
#include <math.h>

#ifdef __min
#undef __min
#endif

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))
#define __abs(x) ((x) < 0 ? (-(x)) : (x))

struct node {
  double a, p[4];
} e[1001] ;

double get(double x, double y) {
  return sqrt(x * x + y * y);
}

double getMin(double x, double y, double z, double w, double delta) {
  return __min(__min(__abs(x - delta), __abs(y - delta)),
	       __min(__abs(z - delta), __abs(w - delta)));
}

int n;

int main(int argc, char *argv[]) {
  int i, j;
  double h = 5, l = 0, last = 0;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%lf %lf %lf %lf %lf",
	  &e[i].a,
	  &e[i].p[0],
	  &e[i].p[1],
	  &e[i].p[2],
	  &e[i].p[3]);
  }
  for (i = 0; i < n; ++i) {
    // add
    l += get(e[i].a - last, h);
    // change h and last
    h = getMin(e[i].p[0],
	       e[i].p[1],
	       e[i].p[2],
	       e[i].p[3], h);
    last = e[i].a;
  }
  l += get(e[n - 1].a - last, __abs(h - 5));
  printf("%.2lf", l);
  return 0;
}

/*
2
4 2 7 8 9
7 3 4.5 6 7
*/


