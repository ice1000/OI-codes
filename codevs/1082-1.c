/*
作者:千里冰封
题目:p1082 线段树练习 3
*/

#include <stdio.h>

#define size 2000010
#define lowbit(x) ((x) & (-(x)))
#define int long long

int tree1[size], tree2[size], num[size], n, q;

void add(int *tree, int idx, int value) {
  if (idx <= n) tree[idx] += value, add(tree, idx + lowbit(idx), value);
}

int sum(int *tree, int idx) {
  return idx ? tree[idx] + sum(tree, idx - lowbit(idx)) : 0;
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
  int i, type, a, b;
  scanf("%lli", &n);
  for (i = 1; i <= n; ++i) {
    scanf("%lli", &num[i]);
    add(tree1, i, num[i] - num[i - 1]);
    add(tree2, i, (i - 1) * (num[i] - num[i - 1]));
  }
  scanf("%lli", &q);
  while (q --> 0) {
    scanf("%lli", &type);
    switch (type) {
    case 1:
      scanf("%lli %lli %lli", &a, &b, &i);
      add(tree1, a, i);
      add(tree1, b + 1, -i);
      add(tree2, a, i * (a - 1));
      add(tree2, b + 1, -i * b);
      break;
    case 2:
      scanf("%lli %lli", &a, &b);
      printf("%lli\n",
          (b * sum(tree1, b) - sum(tree2, b)) -
          ((a - 1) * sum(tree1, a - 1) - sum(tree2, a - 1))
      );
      break;
    }
  }
  return 0;
}

/*
3
1
2
3
2
1 2 3 2
2 2 3
*/

