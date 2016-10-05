#include <stdio.h>
#include <string.h>

int stack[105], i, j, n;
char seq[105];

int main(int argc, char *argv[]) {
	while (scanf("%s", seq) == 1) {
		puts(seq);
		memset(stack, 0, 105 * sizeof(int));
		n = j = 0;
		for (i = 0; seq[i]; ++i) {
			if (seq[i] == '(') {
				stack[j++] = i;
			}
			if (seq[i] == ')') {
//				printf("|%i|", j);
				if (j > 0) stack[j--] = 0;
				else seq[i] = '?';
			}
		}
		for (i = 0; seq[i]; ++i) {
			if (seq[i] == '?') {
				putchar('?');
				continue;
			}
			if (n < j && stack[n] == i) {
				putchar('$');
				++n;
				continue;
			}
			putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}

/*
((ABCD(x)
)(rttyy())sss)(
*/

