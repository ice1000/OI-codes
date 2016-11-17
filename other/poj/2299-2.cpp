#include <stdio.h>
#include <string.h>
#include <algorithm>
#define size 1000010
#define lowbit(x) ((x) & (-(x)))

int tree[size + 10], n, after_tree[size + 10];

struct Node {
	int v, p;
	const bool operator<(const Node& o) const {
		return v < o.v;
	}
} a[size + 10];

int sum(int *tree, int idx) {
	return idx > 0 ? tree[idx] + sum(tree, idx - lowbit(idx)) : 0;
}

void add(int *tree, int n, int idx) {
	if (idx < n) ++tree[idx], add(tree, n, idx + lowbit(idx));
}

int main(int argc, const char *argv[]) {
	int i, j;
	long long t = 0;
	while (scanf("%i", &n) != EOF) {
		if (!n) return 0;
	  memset(a, 0, sizeof(a));
	  memset(tree, 0, sizeof(tree));
	  memset(after_tree, 0, sizeof(after_tree));
	  t = 0;
		for (i = 0; i < n; ++i) {
			scanf("%i", &a[i].v);
			a[i].p = i+1;
		}
		std::sort(a, a + n);
		for (j = 1, i = 0; i <= n; ++i, ++j) {
			after_tree[a[i].p - 1] = j;
			if (a[i].v == a[i + 1].v) --j;
		}
//    for (i = 0; i < n; ++i) {
//      printf("%i ", after_tree[i]);
//    }
//    puts("");
		for (i = 0; i < n; ++i) {
//      printf("%i ", after_tree[i]);
			add(tree, n + 1, after_tree[i]);
			t += 1 + i - sum(tree, after_tree[i]);
		}
//		puts("");
		printf("%lli\n", t);
	}
	return 0;
}

/*
5 9 1 0 5 4 3 1 2 3 0

33 1 100 20 43 43
*/


