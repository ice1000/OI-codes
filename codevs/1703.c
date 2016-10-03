/*
作者:千里冰封
题目:p1703 指数判定
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
	int n;
	double i, j;
	scanf("%i", &n);
	while (n--) {
		scanf("%lf %lf", &i, &j);
		printf("%.3lf\n", (log(i) / log(j)));
	}
	return 0;
}
/*
4 1 2 3 4
 */


