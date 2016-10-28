#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 0xffffff

#ifdef __max
#undef __max
#undef __min
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))
#define __min(x, y) ((x) < (y) ? (x) : (y))

typedef struct node {
  int min, max;
} node;

int n, a[101][101];
node dp[101][101];

int main(int argc, const char *argv[]) {
	int i, j, max, min, x, y;
	node no = *(node *)malloc(sizeof(node));
	scanf("%i", &n);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			scanf("%i", &a[i][j]);
		}
	dp[0][0].max = a[0][0];
	dp[0][0].min = a[0][0];
	for (i = 1; i < n; ++i) {
	  dp[i][0].max = __max(a[i][0], dp[i - 1][0].max);
	  dp[i][0].min = __min(a[i][0], dp[i - 1][0].min);
	  dp[0][i].max = __max(a[0][i], dp[0][i - 1].max);
	  dp[0][i].min = __min(a[0][i], dp[0][i - 1].min);
  }
	for (i = 1; i < n; ++i) {
		for (j = 1; j < n; ++j) {
		  x = dp[i][j - 1].max - dp[i][j - 1].min;
		  y = dp[i - 1][j].max - dp[i - 1][j].min;
		  if (x > y) {
		    max = dp[i - 1][j].max;
		    min = dp[i - 1][j].min;
      } else {
        max = dp[i][j - 1].max;
        min = dp[i][j - 1].min;
      }
			if (a[i][j] > max) max = a[i][j];
			dp[i][j].max = max;
			if (a[i][j] < min) min = a[i][j];
			dp[i][j].min = min;
		}
	}
//  for (i = 0; i < n; ++i) {
//		for (j = 0; j < n; ++j) {
//			printf("[%i, %i] ", dp[i][j].max, dp[i][j].min);
//		}
//		puts("");
//	}
	--n;
	printf("%i", dp[n][n].max - dp[n][n].min);
	return 0;
}

/*
5
1 1 3 6 8
1 2 2 5 5
4 4 0 3 3
8 0 2 3 4
4 3 0 2 1
*/

