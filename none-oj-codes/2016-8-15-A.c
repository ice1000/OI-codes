#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[1005];
int l;

//int fuck(int left, int right) {
//	int i;
//	for (i = 0; ; ++i) {
//		if (left < i || right + i >= l || a[left - i] == ';' || !a[right + i] == ';' || a[left - i] != a[right + i]) return i;
//	}
//}

int damn(int left, int right) {
	while (left < right) if (a[left++] != a[right--]) return 0;
	return 1;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int dp[1005];

int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		scanf("%s", a + 1);
		l = strlen(a + 1);
		dp[0] = 0;
		int i, j;
		for (i = 1; i <= l; ++i) dp[i] = 0xFFFFF;
		for (i = 1; i <= l; ++i)
			for (j = 1; j <= i; ++j)
				if (damn(j, i)) dp[i] = min(dp[i], dp[j - 1] + 1);
		printf("%d\n", dp[l]);
//		int shit = l;
//		int i, bitch = 0, max, ma, mb, suck;
//		while (shit) {
//			++bitch;
//			max = 0;
//			for (i = 0; i < l; ++i) {
//				if (a[i]) {
//					suck = fuck(i, i);
//					if (suck > max) {
//						max = suck;
//						ma = mb = i;
//					}
//					if (i < l - 1 && a[i + 1]) {
//						suck = fuck(i, i + 1);
//						if (suck >= max) {
//							max = suck;
//							ma = i;
//							mb = i + 1;
//						}
//					}
//				}
//			}
//			shit -= max * 2;
//			if (ma == mb) ++shit;
//			for (i = ma - max + 1; i < mb + max; ++i) a[i] = ';';
//		}
//		printf("%d\n", bitch);
	}
	return 0;
}

