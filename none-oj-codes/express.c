#include <stdio.h>

#define size 100010 << 1
#define __max(a, b) (((a) > (b)) ? (a) : (b))
#define __min(a, b) (((a) < (b)) ? (a) : (b))

int n, x[size], y[size], s[size];

double binSearch(double l, double r) {
	if (r - l < 0.005) return l;
	double mid = (l + r) / 2, timeNow = 0;
	int i;
	for (i = 0; i < n; ++i) {
		if (mid * (x[i] - timeNow) >= s[i]) {
			timeNow = x[i];
		} else if (mid * (y[i] - timeNow) >= s[i]) {
			timeNow += s[i] * 1.0 / mid;
		} else return binSearch(mid, r);
	}
	return binSearch(l, mid);
}

int main(int argc, const char *argv[]) {
	freopen("express.in", "r", stdin);
	freopen("express.out", "w", stdout);
	int i, j, k, l;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%i %i %i", &x[i], &y[i], &s[i]);
	}
	printf("%.2lf", binSearch(x[0] / s[0], 2e8));
	return 0;
}

/*
3
1 2 2
6 6 2
7 8 4
*/

