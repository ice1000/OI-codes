#include <stdio.h>

int i, j, q, n, a[205][205], k, c, b, d, e, h[205], max, mxa;
long long tt;

int main(int argc, char* argv[]) {

	scanf("%d %d", &n, &q);

	for (i = 1; i < n; ++i) {
		scanf("%d %d %d", &c, &b, &j);
		a[c][b] = j;
	}


	printf("%I64d", tt);

	return 0;

}

/*

5 2
1 3 1
1 4 10
2 3 20
3 5 20

*/
