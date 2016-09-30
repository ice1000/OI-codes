/*
作者:千里冰封
题目:p1080 线段树练习
*/

#include <stdio.h>
#define lowbit(x) ((x) & (-(x)))
int a[100001], n;
int sum(int n) {
  return n ? a[n] + sum(n - lowbit(n)) : 0;
}
int add(int u, int v) {
  if (u <= n) {
    a[u] += v;
    add(u + lowbit(u), v);
  }
}
int main(int argc, char *argv[]) {
  int i, j, m, k;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) {
    scanf("%i", &j);
    add(i, j);
  }
  scanf("%i", &m);
  while (m--) {
    scanf("%i %i %i", &i, &j, &k);
    if (i == 1) add(j, k);
    else printf("%i\n", sum(k) - sum(j - 1));
  }
  return 0;
}

/*
6
4
5
6
2
1
3
4
1 3 5
2 1 4
1 1 9
2 2 6
 */

