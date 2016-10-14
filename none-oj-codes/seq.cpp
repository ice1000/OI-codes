/*
 * 谜之代码
 * 写完之后就看不懂系列 
 */

#include <stdio.h>
#include <stdlib.h>

int *save;
const int fuck = 1000000007;
int i, j, t, q, min = fuck, max = -1, a, b, c, d;
int query[1001];

int main(int argc, char* argv[]) {
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	scanf("%d", &t);
	for (i = 0; i < t; ++i) {
		scanf("%d", &query[i]);
		if (query[i] > max) max = query[i];
		if (query[i] < min) min = query[i];
	} 
	save = (int*) malloc ((max - min + 2) * sizeof(int));
	a = b = c = 1;
	for (i = 0; i < min - 1; ++i) {
		d = (a + c) % fuck;
		a = b;
		b = c;
		c = d;
	}
	save[0] = a;
	save[1] = b;
	save[2] = c;
	for (i = 3; i <= max - min + 1; ++i) save[i] = (save[i - 1] + save[i - 3]) % fuck;
	for (i = 0; i < t; ++i) printf("%d\n", save[query[i] - min]);
	return 0;
}

/*
2 5
1 1 1 2 3 4 6 9 13 19
  0 1 2

*/
