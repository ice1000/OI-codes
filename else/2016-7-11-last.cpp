#include <stdio.h>

typedef struct {
	int pos;
	char gender;
	char direction;
} Person ;

int max(int x, int y) {
	return x > y ? x : y;
}

int del(int x, int y) {
	return x - y > 0 ? x - y : y - x;
}

int i, j, n, l, v, t = 0;
Person p[1000010];
int main(int argc, char* argv[]) {
	freopen("last.in", "r", stdin);
	freopen("last.out", "w+", stdout);
	scanf("%i %i %i", &n, &l, &v);
	int mac = -1, dir;
	double t, d;
	for(i = 0; i < n; i++) {
		scanf("%i %c %c",
				&p[i].pos,
				&p[i].gender,
				&p[i].direction
		);
		dir = p[i].direction == 'E' ? 1 : 0;
		int k = dir ? l - p[i].pos : p[i].pos;
		d += k;
		mac = max(mac, k);
	}
	printf("%.2lf %.2lf", mac / v, d);
	return 0;
}
