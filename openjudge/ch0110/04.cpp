#include <stdio.h>
#include <algorithm>

struct ass {
  int c, e, m, s, sum;
  bool operator<(const ass& o) const {
    if (sum ^ o.sum) return sum < o.sum;
    if (c ^ o.c) return c < o.c;
    return s > o.s;
  }
} a[10001];

int main(int argc, char *argv[]) {
  int n, i;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i %i %i", &a[i].c, &a[i].m, &a[i].e);
    a[i].sum = a[i].c + a[i].e + a[i].m;
    a[i].s = i + 1;
  }
  std::sort(a, a + n);
  for (i = n - 1; i >= n - 5; --i) printf("%i %i\n", a[i].s, a[i].sum);
  return 0;
}
/**
8
80 89 89
88 98 78
90 67 80
87 66 91
78 89 91
88 99 77
67 89 64
78 89 98
*/

