#include <math.h>
#include <stdio.h>
#include <string.h>

#define int long long

inline int in() {
	int ch = getchar(), x = 0;
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

char a[100010], b[100010];
int aa, bb;
int alpha[30], alphb[30];
int ans;

#undef int

int main(int argc, const char *argv[]) {
#define int long long
	int i;
	scanf("%s %s", a, b);
	aa = strlen(a), bb = strlen(b);
	for (i = 1; i < aa; i++) alpha[a[i] - 'a' + 1]++;
	for (i = 0; i < bb - 1; i++) alphb[b[i] - 'a' + 1]++;
	ans = 1ll * aa * bb;
	for (i = 1; i <= 26; i++) ans -= 1ll * alpha[i] * alphb[i];
	printf("%lli\n", ans);
	return 0;
}
