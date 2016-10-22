#include <stdio.h>
#include <math.h>
#include <string.h>

char a[10001];
int mk[30], n;
int h26 = 1;

int findMax(int idx, int dir) {
	int i, ret, jz = h26;
	if (dir) {
		for (i = 0; i < n; ++i) {
			ret += jz * (a[(idx - i + n) % n] - 'a');
			jz /= 26;
		}
	} else {
		for (i = 0; i < n; ++i) {
			ret += jz * (a[(idx + i) % n] - 'a');
			jz /= 26;
		}
	}
	return ret;
}

int main(int argc, char *argv[]) {
	freopen("Donut.in", "r", stdin);
	freopen("Donut.out", "w", stdout);
	int i, j, k = 0, l, d, e, f;
	scanf("%i", &n);
	getchar();
	for (i = 0; i < n; ++i) {
		a[i] = getchar();
		++mk[a[i] - 'a'];
		h26 *= 26;
	}
	i = 'z' - 'a';
	while (!mk[i]) --i;
	for (j = 0; j < n; ++j) {
		if (a[j] == i + 'a') {
			l = findMax(j, 0);
			if (l > k) {
				k = l;
				e = j;
				d = 0;
			}
			printf("", k, d);
			l = findMax(j, 1);
			if (l > k) {
				k = l;
				e = j;
				d = 1;
			}
			printf("", k, d);
		}
	}
	printf("%i %i", ++e, d);
	return 0;
}

/*
4
abab
*/
