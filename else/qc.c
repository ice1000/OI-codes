#include <stdio.h>

int n, m, s, w[1000], v[1000], l[1000], r[1000], min = 0xFFF;

void init() {
	freopen("qc.in", "r", stdin);
//	freopen("qc.out", "w+", stdout);
}

// i是区间编号，x是目前查找的w值
int getValue(int i, int x) {
	int a ,ret = 0;
	for(a = l[i]; a < r[i]; a++) {
		if(w[a] >= x)
			ret += a * v[a];
	}
	return ret;
}

void search(int le, int ri) {
	if(le > ri) return ;
	int mid = (le + ri + 1) / 2, i, y = 0;
	for(i = 0; i < m; i++) {
		y += getValue(i, mid);
	}
	if(y < min) min = y;
	search(le, mid - 1);
	search(mid + 1, ri);
}

int main(int argc, char* argv[]) {
	init();
	int i, j, dfs =-1;
	scanf("%d%d%d", &n, &m, &s);
	for(i = 0; i < n; i++) {
		scanf("%d%d", &w[i], &v[i]);
		if(w[i] > dfs) dfs = w[i];
	}
	for(i = 0; i < m; i++) {
		scanf("%d%d", &l[i], &r[i]);
	}
	search(0, dfs);
	printf("%d", min);
	return 0;
}
