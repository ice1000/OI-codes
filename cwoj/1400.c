#include <stdio.h>
#include <math.h>

const double pi = 3.14159265358979;

int main(int argc, const char *argv[]) {
  double a, b, c, d, e, f, p, s, r, h;
  scanf("%lf %lf %lf", &a, &b, &c);
  d = sqrt(a * a + b * b), e = sqrt(a * a + c * c), f = sqrt(c * c + b * b);
  p = (d + e + f) / 2;
  r = a * b * c / 2 / (sqrt(p * (p - f) * (p - e) * (p - d)) + a * b / 2 + b * c / 2 + c * a / 2);
  printf("%.2lf", 4 * pi * r * r * r / 3);
  return 0;
}

