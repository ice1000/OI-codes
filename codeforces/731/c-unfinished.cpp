#include <stdio.h>
#include <math.h>

#define size 200005

// md 尼玛这题是差分约束
// 我不会啊啊啊啊

int c[size], l[size], r[size];
bool shit[size][size];
int n, m, k;

int main(int argc, char *argv[]) {
	int i, j, x, y, z, tot = 0;
	scanf("%i %i %i", &n, &m, &k);
	for (i = 0; i < n; ++i) scanf("%i", &c[i]);
	for (i = j = 0; j < m; ++j) {
		scanf("%i %i", &l[i], &r[i]);
		if (c[l[i]] != c[r[i]]) ++i;
	}
	if (!i) {
		putchar('0');
		return 0;
	}
	m = i;
	for (i = 0; i < m; ++i) {
		if (!shit[c[l[i]]][c[r[i]]]) {
			++shit[c[l[i]]][c[r[i]]], ++shit[c[r[i]]][c[l[i]]];
			++tot;
		}
	}
	return 0;
}
