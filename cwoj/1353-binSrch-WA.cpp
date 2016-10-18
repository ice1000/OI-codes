#include <stdio.h>

long long a[2000005];

long long find(int l, int r, int n) {
  if (l >= r) return r;
  int mid = (l + r) >> 1;
  return a[mid] == n ? a[mid] : a[mid] > n ? find(l, mid, n) : find(mid + 1, r, n);
}

int main(int argc, char *argv[]) {
  int i, j, n, s, min = 0xffffff;
  scanf("%i %i", &n, &s);
  for (i = 1; i <= n; ++i) {
    scanf("%i", &j);
    a[i] = a[i - 1] + j;
    j = find(1, i, a[i] - s);
    if (a[i] - s >= a[1] && min > i - j)
      min = i - j + 1;
  }
  printf("%i", min);
  return 0;
}

/*
6 10
1 2 1 2 5 3
*/

