#include <stdio.h>

char map[10005];

int abs(int a) {
	return a > 0 ? a : -a;
}

int main(int argc, char* argv[]) {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);

	map[a]++;
	map[b]++;
	map[c]++;

	map[a + b]++;
	map[a + c]++;
	map[b + c]++;

	map[a + b + c]++;

	map[abs(a - b)]++;
	map[abs(a - c)]++;
	map[abs(b - c)]++;

	map[abs(a + b - c)]++;
	map[abs(c + a - b)]++;
	map[abs(b + c - a)]++;
	if (abs(a - b) < a) map[abs(a + a - b)]++;
	if (abs(a - c) < a) map[abs(a + a - c)]++;
	if (abs(b - c) < b) map[abs(b + b - c)]++;
	if (abs(b - a) < b) map[abs(b + b - a)]++;
	if (abs(c - b) < c) map[abs(c + c - b)]++;
	if (abs(c - a) < c) map[abs(c + c - a)]++;
	map[abs(a - b - c)]++;
	map[abs(b - c - a)]++;
	map[abs(c - a - b)]++;

	c = 0;
	for (a = 1; a < 10005; a++) if (map[a]) c++;
	printf("%d", c);
	return 0;
}
