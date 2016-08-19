#include <stdio.h>
#include <string.h>
#define __max(x, y) ((x) > (y) ? (x) : (y))

char s[105];

int main(int argc, char* argv[]) {
	int i, j, k, a, b, c, x, y;
	int max = 0;
	scanf("%s", s);
	for (i = 0; i < strlen(s); ++i) {
		for (j = i + 1; j < strlen(s); ++j) {
			// s[i] and s[j]
			a = i, b = j, c = 0;
			while (s[a++] == s[b++]) c++;
			max = __max(max, c);
		}
	}
	printf("%d", max);
	return 0;
}
