#include <stdio.h>
#include <list>

#define int long long

int a[1000010 << 1], n;

#undef int
int main(int argc, const char *argv[]) {
#define int long long
	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);
	int i, j, k, ans = 0, tmp;
	scanf("%lli", &n);
	for (i = 0; i < n; ++i) {
		scanf("%lli", &a[i]);
	}
	for (i = 0; i < n; ++i) {
		tmp = a[i];
		k = j = i;
		a[i] = 0;
		while (tmp < 0) {
			if (--j > 0 && a[j] > a[k]) {
				a[j] = 0;
				tmp += a[j];
			} else if (++k <= n) {
				a[k] = 0;
				tmp += a[k];
			} else {
			  printf("%lli\n", i);
			  puts("-1");
			  return 0;
      }
			--ans;
		}
		a[k] = tmp;
		if (tmp >= 0) ++ans;
	}
	printf("%lli", ans);
}

