#include <stdio.h>

const int size = 0xfffff;
int uset[size];

int find(int n) {
  if (n != uset[n]) uset[n] = find(uset[n]);
  return uset[n];
}

void merge(int a, int b) {
  int x = find(a), y = find(b);
  if (x != y) uset[x] = y;
}

int main(int argc, char *argv[]) {
  int n, m, i, j, a, b, c, d = 0;
  while (++d) {
    c = 0;
    scanf("%i %i", &n, &m);
    if (!m and !n) break;
    for (i = 1; i <= n; ++i) uset[i] = i;
    for (i = 1; i <= m; ++i) {
      scanf("%i %i", &a, &b);
      merge(a, b);
    }
    for (i = 1; i <= n; ++i)
      if (uset[i] == i) c++;
    printf("Case %i: %i\n", d, c);
  }
  return 0;
}

