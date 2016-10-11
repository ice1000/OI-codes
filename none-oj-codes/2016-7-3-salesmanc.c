#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int n, a[15][15], min = 0xFFF;
int p[15];
/**
 * @param n the number now.
 * @param d the dis that has passed.
 * @param p stores the passed towns.
 */
void dfs(int n, int d, int s) {
//  剪枝
	if(d + a[n][0] >= min) return ;
//	printf("%d\n", d);
	int i;
//  此时d绝对比min小（因为前面已经剪枝了
	if(s >= n) {
		d += a[n][0];
		min = d;
		return ;
	}
	for(i = 0; i < n; i++) {
		if(!p[i]) {
			p[i] = 1;
			dfs(i, d + a[n][i], s+1);
			p[i] = 0;
		}
	}
}

int main(int argc, char* argv[]) {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]);

	p[0] = 1;
	dfs(0, 0, 1);
	printf("%d", min);
	return 0;
}
