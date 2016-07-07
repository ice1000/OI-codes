/*
作者:千里冰封
*/

#include <stdio.h>
#include <string.h>

const int size = 1000 + 5;

int n, m, x;
int t[size][size];

int min(int x, int y) {
	return x > y ? y : x;
}
int max(int x, int y) {
	return x < y ? y : x;
}

void init() {
	freopen("sword.in", "r", stdin);
	freopen("sword.out", "w+", stdout);
}

void test() {
	int i, j;
	for(i = 1; i <= n; i++) {
		for(j = 1; j <= n; j++) {
			printf("%d ", t[i][j]);
		}
		putc('\n', stdout);
	}
}

int main(int argc, char *argv[]) {
//	init();
	int k, j;
	int i;
	memset(t, 1, sizeof(t));
	scanf("%d %d %d", &n, &m, &x);
	for (i = 0; i < m; ++i) {
		int a, b, l;
		scanf("%d %d %d", &a, &b, &l);
		t[a][b] = min(t[a][b], l);
//		t[a][b] = l;
	}
	test();
	for (k = 1; k <= n; ++k)
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j) {
				t[i][j] = min(t[i][k] + t[k][j], t[i][j]);
			}
	k = 0;

	for(i = 1; i <= n; i++)
		k = max(k, t[i][x] + t[x][i]);
	printf("%d", k);
	return 0;
}

/*
4 8 2
1 2 4
1 3 2
1 4 7
2 1 1
2 3 5
3 1 2
3 4 4
4 2 3
 * 
 * 
 * */