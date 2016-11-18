#include <stdio.h>
#include <string.h>

#define size 200010
#define lowbit(x) ((x) & (-(x)))

int tree[size], n;

void add(int idx, int num) {
	if (idx <= n) tree[idx] += num, add(idx + lowbit(idx), num);
}

int sum(int idx) {
	return idx >= 1 ? tree[idx] + sum(idx - lowbit(idx)) : 0;
}

char buffer[10];

int main(int argc, const char *argv[]) {
	int i, j, t, cnt;
	scanf("%i", &t);
	for (cnt = 1; cnt <= t; ++cnt) {
		scanf("%i", &n);
		memset(tree, 0, sizeof(tree));
		printf("Case %i:\n", cnt);
		for (i = 1; i <= n; ++i) {
			scanf("%i", &j);
			add(i, j);
		}
		while (buffer[0] != 'E') {
			scanf("%s", buffer);
			switch (buffer[0]) {
			case 'A':
			  scanf("%i %i", &i, &j);
				add(i, j);
				break;
			case 'S':
			  scanf("%i %i", &i, &j);
				add(i, -j);
				break;
			case 'Q':
			  scanf("%i %i", &i, &j);
				printf("%i\n", sum(j) - sum(i - 1));
				break;
			}
		}
		buffer[0] = '%';
	}
	return 0;
}

/*
2
10
1 2 3 4 5 6 7 8 9 10
Query 1 3
Add 3 6
Query 2 7
Sub 10 2
Add 6 3
Query 3 10
End
10
1 2 3 4 5 6 7 8 9 10
Query 1 3
Add 3 6
Query 2 7
Sub 10 2
Add 6 3
Query 3 10
End
*/

