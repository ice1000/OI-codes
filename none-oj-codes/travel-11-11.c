#include <stdio.h>
#include <string.h>

#define ms(x, y) (memset(x, y, sizeof(x)))
#define size 100010 << 1

int n, head[size], next[size], to[size];

int main(int argc, const char *argv[]) {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	int i, j, k;
	long long l = 0, shit = 1;
	scanf("%i", &n);
	for (i = 4; i <= n; ++i) {
		shit *= i;
	}
	ms(head, -1);
	ms(next, -1);
	for (i = 1; i < n; ++i) {
		scanf("%i %i", &j, &k);
		next[l] = head[j];
		to[l] = k;
		head[j] = l++;

		next[l] = head[k];
		to[l] = j;
		head[k] = l++;
	}
	l = 0;
	for (i = 1; i <= n; ++i) {
		for (j = head[i]; ~j; j = next[j]) {
			for (k = head[to[j]]; ~k; k = next[k]) {
				if (to[k] != i) {
					++l;
//					printf("%i %i %i\n", i, to[j], to[k]);
				}
			}
		}
	}
	printf("%lli", shit - (l >> 1));
	return 0;
}
/*
4
1 2
1 3
1 4
*/

