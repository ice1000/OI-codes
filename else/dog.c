
/*

#include <stdio.h>

int mac(int x, int y) {
	return x > y ? x : y;
}

int a[51][51], e, m[51][51];

int main(int argc, char* argv[]) {
	freopen("dog.in", "r", stdin);
//	freopen("dog.out", "w+", stdout);
	scanf("%d", &e);
	int i, j, nor = 1, k, count = 0, get = 0;
	for(i = 0; i < e; i++) {
		for(j = 0; j < e; j++) {
			scanf("%d", &a[i][j]);
			count += a[i][j];
			if(a[i][j] < 0) nor = 0;
		}
	}
	if(nor) {
		printf("%d", count);
	} else {
//		dfs(0, 0, 0);
		for(i = 0; i < e; i++) {
			int ent = 0, max = 0, thisent = 0;
			for(k = ent; k < e; k++) {
				for(j = k; j < e; j++) {
					a[i][j] = mac(a[i][j], a[i][j - 1] + a[i][j]);
					if(mac(max, a[i][j]) == max) thisent = j;
					a[i][j] = 0;
				}
			}
			for(k = ent; k >= 0; k--) {
				for(j = k; j >= 0; j--) {
					a[i][j] = mac(a[i][j], a[i][j + 1] + a[i][j]);
					if(mac(max, a[i][j]) == max) thisent = j;
					a[i][j] = 0;
				}
			}
			ent = thisent;
			if(i < e - 1) {
				a[i + 1][ent] += max;
			}
		}
		for(i = 0; i < e; i++) {
			get = mac(get, a[e - 1][i]);
		}
		printf("%i", get);
	}
	return 0;
}
*/

#include <stdio.h>

int mac(int x, int y) {
	return x > y ? x : y;
}

int max;
int a[51][51], e, m[51][51], l[51];
//void dfs(int x, int y, int h) {
//	if(l[x]) {
//		h += l[x];
//		x++;
////		printf("%d\n", h);
//	}
//	if( x < 0 || x >= e || y < 0 || y >= e || m[x][y] ) return ;
//	m[x][y] = 1;
//	int temp = a[x][y];
//	h += temp;
//	a[x][y] = 0;
//	printf("x = %d, y = %d, h = %d\n", x+1, y+1, h);
////	if(y >= e - 1)
//	max = mac(max, h);
//	dfs(x, y+1, h);
//	dfs(x, y-1, h);
//	dfs(x+1, y, h);
//	m[x][y] = 0;
//	a[x][y] = temp;
//}

void dfs(int y, int x, int h) {
	if(y >= e || x < 0 || x >= e) return ;
	if(m[x][y]) return ;
	m[x][y] = 1;
	int temp = a[x][y];
	a[x][y] = 0;
	h += temp;
//	printf("x = %d, y = %d, h = %d\n", x+1, y+1, h);
	max = mac(max, h);
	dfs(x, y+1, h);
	dfs(x+1, y, h);
	dfs(x-1, y, h);
	m[x][y] = 0;
	a[x][y] = temp;
}

int main(int argc, char* argv[]) {
	freopen("dog.in", "r", stdin);
	freopen("dog.out", "w+", stdout);
	scanf("%d", &e);
	int i, j, nor = 1, count;
	for(i = 0; i < e; i++) {
		int norl = 1;
		for(j = 0; j < e; j++) {
			scanf("%d", &a[i][j]);
			l[i] += a[i][j];
			if(a[i][j] < 0) {
				nor = 0;
				norl = 0;
			}
		}
		count += l[i];
		if(!norl) {
			l[i] = 0;
		}
	}

//	for(i = 0; i < e; i++) printf("l[%d] = %d\n", i, l[i]);

	if(nor) {
		printf("%i", count);
	}
	else {
		dfs(0, 0, 0);
		printf("%i", max);
	}
	return 0;
}


