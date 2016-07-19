#include <stdio.h>
#include <memory.h>

struct {
	int state;
	int value;
} r[510][510];

int main(int argc, char* argv[]) {
	freopen("problem.in", "r", stdin );
	freopen("problem.out","w+",stdout);
	int cnt, n, m, k, j, i, cnt_i, l1, l2, can = 1;
	scanf("%i", &cnt);
	for(cnt_i = 1; cnt_i <= cnt; cnt_i++) {
		scanf("%i %i", &n, &m);
		memset(r, 0, sizeof(r[0][0]) * n * n);
		for(i = 1; i <= m; i++) {
			scanf("%i %i", &l1, &l2);
			r[l1][l2].state = 1;
			r[l2][l1].state = 1;
		}
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= n; j++) {
				scanf("%i", &r[i][j].value);
			}
		}
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= n; j++) {
				for(k = 1; k <= n; k++) {
					if(r[i][k].state && r[k][j].state) {
						r[i][j].state = 1;
						if(r[i][j].value && !r[i][j].state ||
						        r[i][j].value == -1 && r[i][j].state) {
							can = 0;
		//					printf("mark");
						}
					}
				}
			}
		}
		printf("Case #%d: %s\n", cnt_i, can ? "Yes" : "No");
	}
	return 0;
}
/*
3
4 5
1 2
1 3
1 4
2 3
2 4
0 5
5 5
5 0
5 5
5 5
0 4
5 5
4 0
4 4
1 2
1 3
2 3
2 4
0 4
4 4
4 0
4 5
4 4
0 4
4 5
4 0
4 2
1 2
2 3
0 3
3 -1
3 0
4 -1
3 4
0 -1
-1 -1
-1 0

*/
