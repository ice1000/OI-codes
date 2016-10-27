#include <stdio.h>
#include <stdlib.h>

int n;
char seq[101];

int main(int argc, const char *argv[]) {
  freopen("ball.in", "r", stdin);
  freopen("ball.out", "w", stdout);
	int i, j, begin, top, step = 0;
	scanf("%i %s", &n, seq);
	for (i = 0; i < n >> 1; ++i) {
	  j = seq[i];
	  seq[i] = seq[n - i - 1];
	  seq[n - i - 1] = j;
  }
	for (begin = 0; seq[begin] == 'R'; ++begin);
	top = n - 1;
	while (begin < n) {
		++step;
		while (seq[top] == 'R' && top > 0) --top;
//		printf("%i\t%i\t%i\n", top, step, begin);
//		system("pause");
		if (top == begin) ++begin;
		seq[top++] = 'R';
		for (; top < n; ++top) seq[top] = 'B';
		--top;
	}
	printf("%i", step);
	return 0;
}

/*
20
BRBRRRRRRRRRRRRRRRRR
*/

