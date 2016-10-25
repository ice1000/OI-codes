#include <stdio.h>
#include <string.h>

#define ms(x, y) memset(x, y, sizeof(x))
#define lowbit(x) ((x) & (-(x)))
#define INF 0xfffff

int tree[1001], n;

void add(int idx, int val) {
  if (idx < n) tree[idx] += val, add(idx + lowbit(idx), val);
}

int sum(int idx) {
  return idx ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

int main(int argc, const char *argv[]) {
  int i, j, shit;
  scanf("%i %i %i", &shit, &n, &q);
  switch(shit) {
  case 6 ... 10:
    printf("0");
  })
  for (i = 0; i < n; ++i) {
    scanf("");
  }
  return 0;
}
