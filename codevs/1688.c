/*
作者:千里冰封
题目:p1688 求逆序对
*/

#include <stdio.h>
#define size 100001
#define lowbit(x) ((x) & (-(x)))

int tree[size], n;

int sum(int idx) {
  return idx ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

void add(int idx) {
	if (idx < size) ++tree[idx], add(idx + lowbit(idx));
}

int main(int argc, const char *argv[]) {
  int i, j;
  unsigned t;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) {
    scanf("%i", &j);
    add(j);
    t += i - sum(j);
  }
  printf("%u", t);
  return 0;
}
/*
4
3 2 3 2
*/