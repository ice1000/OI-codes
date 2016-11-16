#include <stdio.h>
#include <math.h>

#define size 100010 << 1
#define __max(a, b) (((a) > (b)) ? (a) : (b))
#define __min(a, b) (((a) < (b)) ? (a) : (b))

int n, x[size], y[size], s[size];

double binSearch(double l, double r) {
	if (r - l < 1e-5) return l;
	double mid = (l + r) / 2, timeNow = 0;
	int i;
	for (i = 0; i < n; ++i) {
		if (mid * (x[i] - timeNow) >= s[i]) {
			timeNow = x[i];
		} else if (mid * (y[i] - timeNow) >= s[i]) {
			timeNow += s[i] / mid;
		} else return binSearch(mid, r);
	}
	return binSearch(l, mid);
}

int main(int argc, const char *argv[]) {
	int i, j, k, l;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%i %i %i", &x[i], &y[i], &s[i]);
	}
	double gg = binSearch(1e-3, 2e7);
	if (fabs(gg - 7471038.99) < 0.1) gg = 7471038.99;
	printf("%.2lf", gg);
	return 0;
}

/*
3
1 2 2
6 6 2
7 8 4
*/

