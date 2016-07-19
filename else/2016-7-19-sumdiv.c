#include <stdio.h>
#include <math.h>

long long i, ret;
inline long long pow(long long a, long long b) {
	for(ret = 1, i = 0; i < b; i++)
		ret *= a, ret %= 9901;
	return ret;
}

inline long long get(long long s) {
	for(ret = 0, i = 1; i <= s; i++)
		if(!(s % i)) ret += i, ret %= 9901;
	return ret;
}

int sum[1000010], idx = 0;

int main(int argc, char *argv[]) {
	freopen("sumdiv.in", "r", stdin);
	freopen("sumdiv.out","w+",stdout);
	long long a, b, res = 0, i, j;
	scanf("%I64d %I64d", &a, &b);
//	if(a <= 50 && b <= 10) {
	printf("%I64d", get(pow(a, b)) % 9901);
	return 0;
//	}
//	for(i = 2; i < sqrt(a); i++) {
//		if(a % i) {
//			sum[idx++] = i--;
//			a /= i;
//		}
//	}
//	return 0;
}
