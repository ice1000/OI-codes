// yzh lsw机房发生X关系

#include <stdio.h>
#include <string.h>

#define ms(x, y) (memset(x, y, sizeof(x)))

int main(int argc, const char *argv[]) {
	int i, j, n;
	size_t length_of_a, length_of_b, max;
	char a[1001], b[1001];
	scanf("%i", &n);
	while (n-- > 0) {
		ms(a, 0);
		ms(b, 0);
		scanf("%s %s", a, b);
		length_of_a = strlen(a);
		length_of_b = strlen(b);
		for (i = 0; i < length_of_a; ++i) {
			a[i] -= '0';
		}
		for (i = 0; i < length_of_b; ++i) {
			b[i] -= '0';
		}
		max = length_of_a > length_of_b ? length_of_a : length_of_b;
		for (i = 0; i < max; ++i) {
			b[i] += a[i];
			if (b[i] >= 10) {
				b[i] -= 10;
				++b[i + 1];
			}
		}
		i = 0;
		while (!b[i++]);
		for (--i; b[i] || i < max; ++i) {
			putchar(b[i] + '0');
		}
		putchar('\n');
	}
	return 0;
}
