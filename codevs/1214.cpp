/*
作者:千里冰封
题目:p1214 线段覆盖
*/
#include <stdio.h>
#include <math.h>
#include <algorithm>

int n, ans;

struct anoymous {
  int x, y;
  bool operator<(const struct anoymous& other) const {
    return y < other.y;
  }
} a[101];

int main(int argc, char *argv[]) {
  int i, j, r = -0xffff;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i %i", &a[i].x, &a[i].y);
    if (a[i].x > a[i].y) std::swap(a[i].x, a[i].y);
  }
  std::sort(a, a + n);
  for (i = 0; i < n; ++i) {
    if (a[i].x >= r) {
      ++ans;
      r = a[i].y;
    }
  }
  printf("%i", ans);
  return 0;
}

