#include <stdio.h>
#include <algorithm>
#define size 500006
#define lowbit(x) ((x) & (-(x)))

int tree[size + 10], n, after_tree[size + 10];

struct Node {
  int v, p;
  const bool operator<(const Node& o) const {
    return v < o.v;
  }
} a[size + 10];

int sum(int idx) {
  return idx >= 1 ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

void add(int idx) {
  if (idx <= size) ++tree[idx], add(idx + lowbit(idx));
}

int main(int argc, const char *argv[]) {
  int i, j;
  long long t = 0;
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) {
    scanf("%i", &a[i].v);
//    a[i].v += size >> 1;
    a[i].p = i;
  }
  std::sort(a + 1, a + n + 1);
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

/*
4
3 2 3 2
*/
