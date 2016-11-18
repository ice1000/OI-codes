/*
作者:千里冰封
题目:p1080 线段树练习
*/

#include <stdio.h>

int n, m, len, a[10001];

struct Node {
s	int l, r, ls, rs, c;
} tree[10001];

int make(int l, int r) {
	++len;
	int now = len, mid = (l + r)>>1;
	tree[now].l = l;
	tree[now].r = r;
	tree[now].ls = -1;
	tree[now].rs = -1;
	tree[now].c = 0;
	if (l < r) {
		tree[now].ls = make(l, mid);
		tree[now].rs = make(mid + 1, r);
	}
}

void update(int now, int x, int k) {
	tree[now].c += k;
	if (tree[now].l - tree[now].r) {
		if (x <= (tree[now].l + tree[now].r) / 2) update(tree[now].ls, x, k);
		else update(tree[now].rs, x, k);
	}
}

int last(int now, int l, int r) {
	int mid = tree[now].l + tree[now].r / 2;
	if (tree[now].l == l and tree[now].r == r) return tree[now].c;
	if (r <= mid) return last(tree[now].ls, l, r);
	if (l > mid) return last(tree[now].rs, l, r);
	return last(tree[now].ls, l, mid) + last(tree[now].rs, mid + 1, r);
}

int main(int argc, char *argv[]) {
	int i, j, k;
	scanf("%i", &n);
	make(1, n);
	for (i = 1; i <= n; ++i) scanf("%i", &a[i]);
	for (i = 1; i <= n; ++i) update(1, i, a[i]);
	scanf("%i", &m);
	while (m--) {
		scanf("%i %i %i", &i, &j, &k);
		if (i == 1) update(1, j, k);
		else printf("%i\n", last(1, j, k));
	}
	return 0;
}
