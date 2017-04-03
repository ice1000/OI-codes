/*
作者:千里冰封
题目:p1169 传纸条
*/


#include <stdio.h>
#include <stdlib.h>

struct node {
	int from;
	int to;
	int val;
} a[100001 << 1];
int uset[20001 << 1];
int n;
size_t m;

int compare(const void *a, const void *b) {
	return ((struct node *) a)->val < ((struct node *) b)->val;
}

int find(int shit) {
	return uset[shit] == shit ? shit : (uset[shit] = find(uset[shit]));
}

int main(int argc, char const *argv[]) {
	int i, j, k;
	scanf("%i %i", &n, &m);
	for (i = 0; i < m; ++i) {
		scanf("%i %i %i", &a[i].from, &a[i].to, &a[i].val);
	}
	qsort(a, m, sizeof(struct node), compare);
	for (i = 0; i < (n << 1); ++i) {
//		printf("%i %i %i\n", a[i].from, a[i].to, a[i].val);
		uset[i] = i;
	}
	for (i = 0; i < m; ++i) {
		j = find(a[i].from);
		k = find(a[i].to);
		if (j == k) {
			printf("%i\n", a[i].val);
			return 0;
		}
		uset[j] = find(a[i].to + n);
		uset[k] = find(a[i].from + n);
	}
	printf("0\n");
	return 0;
}

/*
4 6
1 4 2534
2 3 3512
1 2 28351
1 3 6618
2 4 1805
3 4 12884
*/

