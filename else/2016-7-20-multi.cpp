#include <stdio.h>
#include <string.h>

const int mod_root = 10007;

long long fast_plus(long long a, long long b) {
	long long ret = 0;
	while(b) {
		if(b & 1)
			ret = (ret + a) % mod_root;
		b >>= 1;
		a = (a << 1) % mod_root;
	}
	return ret;
}

long long fast_power(long long a, long long b) {
	long long ret = 1;
	while(b) {
		if(b & 1)
			ret = fast_plus(ret, a) % mod_root;
		b >>= 1;
		a = fast_plus(a, a) % mod_root;
	}
	return ret;
}

int main(int argc, char *argv[]) {
	freopen("multi.in", "r", stdin);
	freopen("multi.out","w+",stdout);
	int x, i, j;
	char ii[50], jj[50];
	long long iii = 0, jjj = 0, power, base;
	scanf("%i", &x);
	if(x == 1) {
		scanf("%s %s", ii, jj);
		// parse the f#cking number
		for(i = 0; i < strlen(ii); i++) {
			iii *= 3;
			iii += ii[i] - '0';
		}
		for(i = 0; i < strlen(jj); i++) {
			jjj *= 3;
			jjj += jj[i] - '0';
		}
//		printf("%I64d %I64d\n", iii, jjj);
		power = (jjj - 1) / 9;
		base = jjj % 9;
		printf("%I64d", fast_plus(fast_power(iii, power), base));
	}
	return 0;
}


