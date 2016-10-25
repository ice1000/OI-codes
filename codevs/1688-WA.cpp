#include <stdio.h>
#include <algorithm>
#define lowbit(c) ((c) & (-c))
int tree[100005], n;

struct Node {
	long long data, pos;
	const bool operator<(const struct Node& o) const {
		return data < o.data;
	}
} a[100005];

void add(int idx) {
	if (idx < 100005) ++tree[idx], add(idx + lowbit(idx));
}

int sum(int idx) {
	return idx ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

int main(int argc, const char *argv[]) {
	int i, x, q;
	long long j;
	scanf("%i", &n);
	// li san hua
	for (i = 1; i <= n; ++i) {
		scanf("%lli", &a[i].data);
		a[i].pos = i;
	}
	std::sort(a + 1, a + n + 1);
	j = 0;
//	for (i = 1; i <= n; ++i) printf("<%i>", a[i].pos);
	for (i = 1; i <= n; ++i) {
		x = a[i].pos;
		add(x);
		j += i - sum(x);
	}
	printf("%lli", j);
	return 0;
}

/*
5
100 4844 156410 15413 87414

4 3 2 3 2
*/

