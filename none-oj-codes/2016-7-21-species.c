#include <stdio.h>
#include <math.h>

int animals[100 * 1001][5 + 1];
int most_friendly = -1, n, k, c[5 + 1];

int friendship(int a, int b) {
	int i, ret = 0;
	for (i = 0; i < k - 1; i++)
		ret += abs(animals[a][i] - animals[b][i]) * c[i];
	ret -= abs(animals[a][i] - animals[b][i]) * c[i];
//	printf("i = %i, k = %i", i, k);
//	printf("a = %i, b = %i, ret = %i\n", a, b, ret);
	return ret;
}

int main(int argc, char* argv[]) {
	freopen("species.in", "r", stdin);
	freopen("species.out","w+",stdout);
	int i, j;
	scanf("%i %i", &n, &k);
	for (i = 0; i < k; i++)
		scanf("%i", &c[i]);
	for (i = 0; i < n; i++)
		for (j = 0; j < k; j++) {
			scanf("%i", &animals[i][j]);
// 			100 * 10000, Acceptable for int
//			animals[i][j] *= c[j];
		}
	int f;
	// 听说有小数据？那我就暴力了 23333
	for(i = 0; i < n; i++) {
		for(j = 0; j < i; j++) {
//			if(i == j) {
//				printf("used!\n");
//				continue;
//			}
			f = friendship(i, j);
			if(f > most_friendly)
				most_friendly = f;
		}
	}
	printf("%i\n", most_friendly);
	return 0;
}

/*
5 3 1 2 3 -5 3 2 -2 3 0 0 5 9 3 4 -1 -10 -11 7
*/
