/*
  作者:千里冰封
  题目:p1080 线段树练习
*/

#include <stdio.h>
#define lowbit(x) ((x) & (-(x)))
int a[100001], n;

int sum(int n) {
	return n ? a[n] + sum(n - lowbit(n)) : 0;
}

int add(int u, int v) {
	if (u <= n) a[u] += v, add(u + lowbit(u), v);
}

int main(int argc, char *argv[]) {
	int i, j, m, k, l;
	scanf("%i", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%i", &j);
		add(i, j);
		add(i + 1, -j);
	}
	scanf("%i", &m);
	while (m--) {
		scanf("%i %i", &i, &j);
		if (i == 1) {
			scanf("%i %i", &k, &l);
			add(j, l);
			add(k + 1, -l);
		} else
			printf("%i\n", sum(j));
	}
	return 0;
}

