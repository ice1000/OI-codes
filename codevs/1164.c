/*
作者:千里冰封
题目:p1164 统计数字
*/

#include <stdio.h>
#include <stdlib.h>

int a[200005];

int cmp(const void *x, const void *y) {
	return (*(int *)x) > (*(int *)y);
}

int main(int argc, const char *argv[]) {
	int i, j, save, cnt = 0;
	scanf("%i", &j);
	for (i = 0; i < j; ++i) {
		scanf("%i", &a[i]);
	}
	qsort(a, j, sizeof(a[0]), cmp);
	save = a[0];
	for (i = 0; i <= j; ++i) {
		if (a[i] == save) ++cnt;
		else {
			printf("%i %i\n", save, cnt);
			save = a[i];
			cnt = 1;
		}
	}
	return 0;
}

/*
8
2
4
2
4
5
100
2
100
*/

