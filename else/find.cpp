#include <stdio.h>

const int size = 100001;

int n, m, a[size], b, res = -1;

void init() {
	freopen("find.in", "r", stdin);
	freopen("find.out", "w+", stdout);
}

void find(int l, int r) {
	if(l > r) return ;
	int mid = (l + r + 1) / 2;
	if(a[mid] > b) {
		res = mid;
		find(l, mid - 1);
	} else if(a[mid] < b) {
		find(mid + 1, r);
	} else {
		res = mid + 1;
	}
}

int main(int argc, char* argv[]) {
	init();
	int i, j;
	scanf("%d%d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	j = 0;
	for(j = 0; j < m; j++) {
		int t;
		scanf("%d", &t);
		if(b < t) b = t;
	}
	if(a[n-1] <= b) {
		printf("-1");
	} else {
		find(0, n - 1);
		printf("%d", a[res]);
	}
	return 0;
}
