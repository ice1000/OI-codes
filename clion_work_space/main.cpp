#include <stdio.h>
#include <cmath>

const int size = 110;

int m (int x, int y) {
	return x > y ? x : y;
}

int dp[size][size], a[size];

int get (int b, int e) {
	return abs(a[b] - a[e]) * ( e - b + 1 );
//	return b == e ? a[e] : abs(a[b] - a[e]) * ( e - b + 1 );
}

int main (int argc, char *argv[]) {
//	freopen("remove.in", "r", stdin);
//	freopen("remove.in", "w+", stdout);
	int n = 1, i, j, k;
	scanf("%i", &n);
	for ( i = 0; i < n; scanf("%i", &a[i]), dp[i][i] = a[i], ++i );
	for ( i = 0; i < n; ++i ) {
		for ( j = 0; j < i; ++j ) {
			int big = -1;
			for ( k = j; k < i; k++ ) {
				big = m(big, dp[j][k] + get(k + 1, i));
				dp[j][i] = big;
			}
		}
	}
//	for ( int l = 0; l < n; ++l ) {
//		for ( int i1 = 0; i1 < n; ++i1 ) {
//			printf("%i ", dp[l][i1]);
//		}
//		puts("\n");
//	}
	printf("%i", dp[0][n - 1]);
	return 0;
}

/*
6
54 29 196 21 133 118
*/
