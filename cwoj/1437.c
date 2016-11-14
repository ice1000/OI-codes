#include <stdio.h>

#define size 2000010
#define int long long

int tree_length = size - 1, bi_tree[size];

void add(int x, int value) {
	if (x < tree_length) bi_tree[x] += value, add(x + ((x) & (-(x))), value);
}

int sum(int x) {
	return x ? bi_tree[x] + sum(x - ((x) & (-(x)))) : 0;
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
	int i, j, n, last = -1, ret = 0, continuing = 1;
	scanf("%lli", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%lli", &j);
		if (j < last) {
			++continuing;
			if (continuing > 2) ret -= continuing - 1;
		} else continuing = 1;
		add(j, 1);
		ret += i - sum(j);
		last = j;
	}
	printf("%lli", ret);
	return 0;
}

/*
 * 6 5 3 2 1 6 4
 */
 
