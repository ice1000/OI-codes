#include <bits/stdc++.h>

// 将来报道上要是有了偏差，你们要负责任

double max(double a, double b) {
	return a > b ? a : b;
}

int main(int argc, char *argv[]) {
	double points[502] = {0.0}, fuck = 0.0;
	int n, m, i, u, v, shit;
	while (~scanf("%d%d", &n, &m)) {
		for (i = 1; i <= n; ++i) {
			scanf("%lf", &points[i]);
		}
		while (m--) {
			scanf("%d%d%d", &u, &v, &shit);
			fuck = max(fuck, (points[u] + points[v]) / shit);
		}
		printf("%.15lf\n", fuck);
	}
	return 0;
}
