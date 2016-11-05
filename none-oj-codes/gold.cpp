#include <stdio.h>
#include <string.h>
#include <algorithm>

#define size 5001 << 1

typedef struct node {
  int val, w;
  const bool operator<(const node& o) const {
    return (val * 1.0 / w) > (o.val * 1.0 / o.w);
  }
} node;

node a[size];

int main(int argc, const char *argv[]) {
  freopen("gold.in", "r", stdin);
  freopen("gold.out", "w", stdout);
  int i, j, m, n, ask, ans;
  scanf("%i", &ask);
  while (ask--) {
    ans = 0;
    scanf("%i %i", &n, &m);
    for (i = 0; i < m; ++i) {
      scanf("%i %i", &a[i].w, &a[i].val);
    }
    std::sort(a, a + m);
    for (i = 0; i < m; ++i) {
//      printf("%i %i\n", a[i].val, a[i].w);
      if (n < a[i].w) break;
      n -= a[i].w;
      ans += a[i].val;
    }
    printf("%.2lf\n", ans + (i >= m ? 0.0 : (a[i].val * n * 1.0 / a[i].w)));
  }
  return 0;
}
