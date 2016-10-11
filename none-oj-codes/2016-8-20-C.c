#include <stdio.h>

int fuck[10005];
int dick(double gg, int n, int f) {
	int i, ret;
	if (!gg) return 1;
	for (i = 0; i < n; ++i) {
		ret += fuck[i] / gg;
		if (ret >= f) return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	const double pi = 3.14159265358979323846263383279502884197;
	int bitch, i, n, f, shit;
	double l, r, m;
	scanf("%d", &bitch);
	while (bitch--) {
		scanf("%d %d", &n, &f);
		for (i = 0; i < n; ++i) {
			scanf("%d", &fuck[i]);
			fuck[i] *= fuck[i];
			shit += fuck[i];
		}
		l = 0, r = shit / ++f;
		while (r - l > 0.0000001) {
			m = (l + r) / 2;
			if (dick(m, n, f)) l = m;
			else r = m;
		}
		printf("%.4lf\n", m * pi);
	}
	return 0;
}
