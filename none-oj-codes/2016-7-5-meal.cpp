//
// Created by ice1000 on 2016/7/5.
//
#include <stdio.h>

const int size = 17;

int n, a[size][size];

// 我写出了一颗赛艇的东西！

void init();

int main(int argc, char *argv[]) {
	init();
	int i, j, k;
	scanf("%d", &n);
	n++;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				if (a[i][j] + a[j][k] < a[i][k]) {
					a[i][k] = a[i][j] + a[j][k];
				}
			}
		}
	}
	for (i = j = 0; i < n - 1; i++) {
		j += a[i][i+1];
	}
	j += a[n - 1][0];
	printf("%d", j);
	return 0;
}

void init() {
	freopen("meal.in", "r", stdin);
	freopen("meal.out", "w+", stdout);
}
