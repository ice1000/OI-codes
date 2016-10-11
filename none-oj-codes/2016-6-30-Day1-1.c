#include <stdio.h>

/**
Not the best one.
This will die when data is .
*/

int max;
int a[51][51], e, m[51][51];
void dfs(int y, int x, int h) {
	if(y >= e || x < 0 || x >= e) return ;
	if(m[x][y]) return ;
	m[x][y] = 1;
	int temp = a[x][y];
	a[x][y] = 0;
	h += temp;
//	printf("x = %d, y = %d, h = %d\n", x+1, y+1, h);
	max = max > h ? max : h;
	dfs(x, y+1, h);
	dfs(x+1, y, h);
	dfs(x-1, y, h);
	m[x][y] = 0;
	a[x][y] = temp;
}

int main(int argc, char* argv[]) {
	freopen("dog.in", "r", stdin);
//	freopen("dog.out", "w+", stdout);
	scanf("%d", &e);
	int i, j, nor = 1, count;
	for(i = 0; i < e; i++) {
		for(j = 0; j < e; j++) {
			scanf("%d", &a[i][j]);
			count += a[i][j];
			if(a[i][j] < 0) nor = 0;
		}
	}
	if(nor) {
		printf("%i", count);
	}
	else {
		dfs(0, 0, 0);
		printf("%i", max);
	}
	return 0;
}
