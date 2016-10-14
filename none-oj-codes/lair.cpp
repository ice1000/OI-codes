#include <stdio.h>
#include <algorithm>

using namespace std;

#define __abs(x) (x) > 0 ? (x) : (-(x))

long long a[100005], b[100005], ret;

int main(int argc, char *argv[]) {
	freopen("lair.in", "r", stdin);
	freopen("lair.out", "w", stdout);
	int n, i, j;
	long long middle;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%lli %lli", &a[i], &b[i]);
	}
	sort(a, a + n);
	sort(b, b + n);
	middle = a[n / 2];
	for (i = 0; i < n; ++i) ret += __abs(a[i] - middle);
	middle = b[n / 2];
	for (i = 0; i < n; ++i) ret += __abs(b[i] - middle);
	printf("%lli", ret);
	return 0;
}

/*
5 1 2 2 2 1 3 3 -2 3 3
 */