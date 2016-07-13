#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	freopen("patchouli.in", "r", stdin);
	freopen("patchouli.out", "w+", stdout);
	char p[2001];
	long long c = 0, i, s = 1, k;
	scanf("%s", p);
	scanf("%lli", &k);
	int m = strlen(p);
	for(i = 0; i < m; i++) {
		c += s * (p[m - i - 1] - 'A');
		s *= 25;
	}
//	printf("%lli", c);
	if(!(c % k)) {
		printf("0 0");
	} else {
		printf("-1 -1");
	}
	return 0;
}
