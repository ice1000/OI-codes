#include <stdio.h>
#include <math.h>

const double PI = 3.14159265358979323846263383279502884197;
double l2;
double l1;

double bs(double l, double r) {
	if (r - l < 1e-14) return r;
	double mid = (l + r) / 2;
	return (l1 / sin(mid) * mid > l2) ? bs(l, mid) : bs(mid, r);
}

int main(int argc, char *argv[]) {
	double c, n;
	int i, j;
	scanf("%lf %lf %lf", &l1, &n, &c);
	l2 = (1 + n * c) * l1;
	if (!(l1 * n * c)) puts("0.000");
	else {
		n = bs(0, PI / 2);
		printf("%.3lf\n", l2 / (n + n) * (1 - cos(n)));
	}
	return 0;
}


