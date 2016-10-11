#include <stdio.h>

int bcj[100005];

typedef struct {
	int total;
	int count;
} jjfly ;

int find(int n) {
	if (bcj[n] == n) return n;
	return bcj[n] = find(bcj[n]);
}

jjfly search(int father, int size) {
	int i;
	jjfly fly;
	fly.total = 0;
	fly.count = 0;
	for (i = 1; i <= size; i++)
		if (find(i) == father)
			fly.total += i, fly.count++;
	return fly;
}

void fuck(int size) {
	int i;
	for (i = 1; i <= size; i++) find(i);
}

void merge(int p, int q, int size) {
	//(/O/v/O/)/
	bcj[find(p)] = q;
	fuck(size);
}

int main(int argc, char* argv[]) {
	int m, n, i, j, a, b, c;
	while (scanf("%d %d", &n, &m) != -1) {
		for (i = 1; i <= n; i++) bcj[i] = i;
		while (m--) {
			scanf("%d", &c);
			switch (c) {
				case 1:
					scanf("%d %d", &a, &b);
					merge(a, b, n);
					break;
				case 2:
					scanf("%d %d", &a, &b);
					bcj[a] = b;
					fuck(n);
					break;
				case 3:
					scanf("%d", &a);
					printf("%d %d\n", search(bcj[a], n).count, search(bcj[a], n).total);
					break;
			}
		}
	}
	return 0;
}
