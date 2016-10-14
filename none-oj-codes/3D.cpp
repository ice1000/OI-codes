#include <bits/stdc++.h>

#define __abs(x) (x) > 0 ? (x) : (-(x))

class pos {
public:
	double x, y, z;

	pos() {
		x = 0;
		y = 0;
		z = 0;
	}

	double dis(pos o) {
		return sqrt(pow(x - o.x, 2) + pow(y - o.y, 2));
	}

	double height(pos o) {
		return __abs(z - o.z);
	}
} pos[105];

int main(int argc, char *argv[]) {
//	freopen("3D.in", "r", stdin);
//	freopen("3D.out", "w", stdout);
	int cnt, n, i, j;
	double fuck = 0, shit = 0;
	scanf("%i", &cnt);
	while (cnt--) {
		scanf("%i", &n);
		for (i = 0; i < n; ++i) scanf("%lf %lf %lf", &pos[i].x, &pos[i].y, &pos[i].z);
		for (i = 0; i < n; ++i) {
			
		}
		printf("%.3lf\n", fuck / shit);
	}
	return 0;
}
