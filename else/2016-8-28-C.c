#include <stdio.h>
#define __max(x, y) ((x) > (y) ? (x) : (y))

int get() {
	int fuck;
	scanf("%d", &fuck);
	return fuck;
}

int bucket[100005];
long long dp[100005];

int main(int argc, char* argv[]) {
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) bucket[get()]++;
	for (i = 2; i < 100005; ++i) {
		dp[i] = __max(dp[i - 1], dp[i - 2] + (long long)bucket[i - 1] * (i - 1));
	}
	printf("%I64d", dp[100004]);
	return 0;
}
