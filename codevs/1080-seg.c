/*
作者:千里冰封
题目:p1080 线段树练习
*/

#include <stdio.h>

#define size 200010
#define INF 0x7f7f7f7f;
#define int long long

int n, a[size];

typedef struct Node {
  int val;
} Node;

Node tree[size << 2];

void build(int root, int l, int r) {
	if (l >= r) {
	  tree[root].val = a[l];
	  return;
	}
	int mid = (l + r) >> 1;
	build((root << 1), l, mid);
	build((root << 1) + 1, mid + 1, r);
	tree[root].val = tree[(root << 1)].val + tree[(root << 1) + 1].val;
}

int query(int root, int l, int r, int begin, int end) {
	if (l >  end || r <  begin) return 0;
	if (r <= end && l >= begin) return tree[root].val;
	int mid = (l + r) >> 1;
	return query( (root << 1)     , l      , mid, begin, end) +
	       query(((root << 1) + 1), mid + 1, r  , begin, end);
}

void update(int root, int l, int r, int pos, int val) {
  if (l > r) return;
  if (pos >= l && pos <= r) {
    tree[root].val += val;
    int mid = (l + r) >> 1;
    if (pos < mid) {
      update((root << 1)    , l    , mid, pos, val);
    } else {
      update((root << 1) + 1, mid + 1, r, pos, val);
    }
  }
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
  int i, j, m, k;
  scanf("%lli", &n);
  for (i = 1; i <= n; ++i) {
    scanf("%lli", &a[i]);
  }
	build(1, 1, n);
  scanf("%lli", &m);
  while (m --> 0) {
    scanf("%lli %lli %lli", &i, &j, &k);
    if (i == 1) update(1, 1, n, j, k);
    else printf("%lli\n", query(1, 1, n, j, k));
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

