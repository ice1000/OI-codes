#include <stdio.h>
#include <memory.h>

// a better way 2 do this, but requires C++
void mac(int& x, int y) {
	x = x > y ? x : y;
}

const int length = 100005;

int main(int argc, char* argv[]) {
//	freopen("sequence.in", "r", stdin);
//	freopen("sequence.out", "w+", stdout);
	int i, j, k, a[length], cnt, dp[length], max = 1;
	memset(dp, 0, length * sizeof(dp[0]));
	scanf("%d", &cnt);
	for(i = 0; i < cnt; i++)
		scanf("%d", &a[i]);

	dp[0] = 1;
	for(i = 1; i < cnt; i++) {
		int m = 0;
		for(j = 0; j < i; j++)
			if(a[j] < a[i])
				mac(m, dp[j]);
		dp[i] = ++m;
		mac(max, m);
	}

	printf("%d\n", max);

	max = 0;

	for(i = 0; i < cnt; i++)
		for(j = i + 2; j < cnt; j++)
			for(k = i + 1; k < j; k++)
				if(a[k] > a[i] && a[k] > a[j])
					max++;

	printf("%d", max);

	return 0;
}
