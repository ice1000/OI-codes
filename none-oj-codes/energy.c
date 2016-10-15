#include <stdio.h>

double a[10001];
double k, tot = 0, avg;
int n, min = 0, max = 0;

double find(double l, double r) {
  if (r - l <= 0.000000001) return r;
  double mid = (l + r) / 2, delta;
  delta = 0;
  int i;
  for (i = 0; i < n; ++i) {
    if (a[i] < mid) {
      delta += mid - a[i];
    } else {
      delta -= (a[i] - mid) * k;
    }
  }
//  printf("%.3lf %.3lf\n", delta, mid);
  if (delta == 0.0) return mid;
  else if (delta > 0.0) return find(l, mid);
  else return find(mid, r);
}

int main(int argc, char *argv[]) {
  freopen("energy.in", "r", stdin);
  freopen("energy.out", "w", stdout);
  int i;
  scanf("%i %lf", &n, &k);
  k = (100.0 - k) / 100.0;
  for (i = 0; i < n; ++i) {
    scanf("%lf", &a[i]);
    tot += a[i];
    if (a[i] < a[min]) {
      min = i;
    }
    if (a[i] > a[max]) {
      max = i;
    }
  }
  avg = tot / n;
  printf("%.9lf", find(a[min], avg));
  return 0;
}
