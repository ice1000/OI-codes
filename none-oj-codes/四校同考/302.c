#include <stdio.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define lowbit(x) ((x) & (-(x)))

int color[1001];
int n, c, m, a, b;

int find(int x, int y) {
  int i, j, shit;
  if (x >= y - 1) {
    return -1;
  }
  for (i = 1; i <= c; ++i) {
    shit = 0;
    for (j = x; j <= y; ++j) {
      if (color[j] == i) {
        ++shit;
      }
    }
    if (shit > ((y - x + 1) >> 1)) {
//      printf("|%i|%i|>>", shit, i);
      return i;
    }
  }
  return -1;
}

int main(int argc, char *argv[]) {
  int i, j;
  scanf("%i %i", &n, &c);
  for (i = 1; i <= n; ++i) {
    scanf("%i", &color[i]);
  }
  scanf("%i", &m);
  for (i = 0; i < m; ++i) {
    scanf("%i %i", &a, &b);
    if ((j = find(a, b)) != -1) {
      printf("yes %i\n", j);
    } else {
      printf("no\n");
    }
  }
  return 0;
}

/*
10 3
1 2 1 2 1 2 3 2 3 3
8
1 2
1 3
1 4
1 5
2 5
2 6
6 9
7 10
*/
