#include <stdio.h>
#include <math.h>

#define __abs(x) ((x) < 0 ? (-(x)) : (x))

double PI = 3.14159265358979;

double shit(double x, double y) {
  return sqrt(x * x + y * y);
}

int main(int argc, char *argv[]) {
  int n;
  double x, y, a, b, r, p, k;
  scanf("%i %lf", &n, &r);
  double fuck = PI * r * 2;
  // first
  scanf("%lf %lf", &x, &y);
  p = x;
  k = y;
  while (--n) {
    scanf("%lf %lf", &a, &b);
    fuck += shit(a - x, b - y);
    x = a;
    y = b;
  }
  // end and begin
  fuck += shit(a - p, b - k);
  printf("%.2lf", fuck);
  return 0;
}

