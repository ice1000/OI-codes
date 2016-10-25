/*
作者:千里冰封
题目:p4163 hzwer与逆序对
*/

#include <stdio.h>
#include <stdlib.h>
#define size 1000010
#define lowbit(x) ((x) & (-(x)))

int tree[size + 10], n, after_tree[size + 10];

typedef struct Node {
  int v, p;
} Node ;
Node a[size + 10];
int sum(int idx) {
  return idx >= 1 ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

void add(int idx) {
  if (idx <= size) ++tree[idx], add(idx + lowbit(idx));
}

int cmp(const void *a, const void *b) {
	return ((Node *)a)->v > ((Node *)b)->v;
}

int main(int argc, const char *argv[]) {
  int i, j;
  long long t = 0;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) {
    scanf("%i", &a[i].v);
    a[i].p = i;
  }
  qsort(a + 1, n, sizeof(Node), cmp);
  for (j = i = 1; i <= n; ++i, ++j) {
    after_tree[a[i].p] = j;
    if (j <= n && a[i].v == a[i + 1].v) --j;
  }
//  for (i = 1; i <= n; ++i) {
//    printf("%i ", after_tree[i]);
//  }
//  puts("");
  for (i = 1; i <= n; ++i) {
    add(after_tree[i]);
    t += i - sum(after_tree[i]);
  }
  printf("%lli", t);
  return 0;
}

