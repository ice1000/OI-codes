#include <stdio.h>
#include <stdlib.h>

void init() {
	freopen("magic.in", "r", stdin);
	freopen("magic.out", "w+", stdout);
}

int max(int x, int y) {
	return x > y ? x : y;
}

int min(int x, int y) {
	return x < y ? x : y;
}

int a[10001][10001];

int main() {
//	system("pause");
	int all;
	init();
	scanf("%d", &all);
	while(all--) {
		int i, j, r, c, m = 0xFFF;
		scanf("%d %d", &r, &c);
		for(i = 0; i < r; i++) {
			for(j = 0; j < c; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		for(i = 0; i < r; i++) {
			if(a[i][0] < 1) m = min(m, 1 - a[i][0]);
		}
		for(i = 0; i < c; i++) {
			if(a[0][i] < 1) m = min(m, 1 - a[0][i]);
		}
		for(i = 1; i < r; i++) {
			for(j = 1; j < c; j++) {
				a[i][j] += max(a[i-1][j], a[i][j-1]);
				if(a[i][j] < 1) m = min(m, 1 - a[i][j]);
			}
		}
		printf("%d\n", m);
	}
	return 0;
}
