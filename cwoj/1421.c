#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[]) {
	long long i, n, l, r, ans = 0, ln, rn, j = 0;
	char a[105], started = 1;
	scanf("%s %lli %lli", a, &l, &r);
	--l, --r;
	n = strlen(a);
	ln = l % n;
	rn = (r + 1) % n;
	for (i = ln; started || i != ln; i = (i + 1) % n) {
		started = 0;
		if (i == rn) j = ans;
		if (a[i] == 'B') ++ans;
	}
	printf("%lli", (r - l + 1) / n * ans + j);
	return 0;
}

/// BBRB 4 8

