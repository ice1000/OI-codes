#include <stdio.h>

int row, column, a[101][101], i, j;
int max = -1, max_x, max_y, step;
int min = 10001, min_x, min_y;

void dfs (int x, int y) {
	if ( x < 0 || x >= row || y < 0 || y >= column ) return;
	step++;
	int go = 0xFFF, dir = -1;
	if ( x > 0 && a[x - 1][y] < a[x][y] ) {
		go = a[x][y] - a[x - 1][y];
		dir = 1;
	}
	if ( y > 0 && a[x][y - 1] < a[x][y] && a[x][y] - a[x][y - 1] < go ) {
		go = a[x][y] - a[x][y - 1];
		dir = 2;
	}
	if ( x < row - 1 && a[x + 1][y] < a[x][y] && a[x][y] - a[x + 1][y] < go ) {
		go = a[x][y] - a[x + 1][y];
		dir = 3;
	}
	if ( y < column - 1 && a[x][y + 1] < a[x][y] && a[x][y] - a[x][y + 1] < go ) {
		go = a[x][y] - a[x][y + 1];
		dir = 4;
	}
	if ( go == 0xFFF )
		return;
	else {
		switch ( dir ) {
			case 1:
				dfs(x - 1, y);
				break;
			case 2:
				dfs(x, y - 1);
				break;
			case 3:
				dfs(x + 1, y);
				break;
			case 4:
				dfs(x, y + 1);
				break;
			default:
				break;
		}
	}
}

int main (int argc, char *argv[]) {
	freopen("ski.in", "r", stdin);
	freopen("ski.out", "w+", stdout);
	scanf("%i %i", &row, &column);
	for ( i = 0; i < row; i++ )
		for ( j = 0; j < column; j++ ) {
			scanf("%i", &a[i][j]);
			if ( a[i][j] > max ) {
				max = a[i][j];
				max_x = i;
				max_y = j;
			}
			if ( a[i][j] < min ) {
				min = a[i][j];
				min_x = i;
				min_y = j;
			}
		}
	dfs(max_x, max_y);
	int k = step;
	step = 0;
	dfs(min_x, min_y);
	if ( k < step ) k = step;
	printf("%d", k);
	return 0;
}
/*
5 5
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
 */

