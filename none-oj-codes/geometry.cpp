// πÚ«Û≤ª±¨¡„w
// +1s

#include <stdio.h>
#include <algorithm>

#define int long long
#define format "%lld"

int n, m, x[100005] = { 0 }, y[100005] = { 0 };

int binSearch(int px, int py, int l, int r) {
	if (l >= r) return l;
	int mid = (l + r) >> 1;
	// when py is bigger, turn right
	int res = ((x[mid] - px) * y[mid] - py * x[mid]);
//	printf("%I64d %I64d %I64d %I64d %.2lf\n", l, r, px, py, res);
	if (!res) return mid;
	if (res > 0) return binSearch(px, py, l, mid);
	else return binSearch(px, py, mid + 1, r);
}

#undef int
int main(int argc, char *argv[]) {
#define int long long
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
	int i, j, k;
	scanf(format, &n);
	for (i = 1; i <= n; ++i) scanf(format, &x[i]);
	for (i = 1; i <= n; ++i) scanf(format, &y[i]);
	x[n + 1] = 0xfffff;
	y[n + 1] = 0xfffff;
	std::sort(x, x + n + 2);
	std::sort(y, y + n + 2);
	scanf(format, &m);
	while (m--) {
		scanf(format, &i);
		scanf(format, &j);
		k = binSearch(i, j, 0, n + 1) - 1;
//		while (x[k] == x[k + 1] && y[k] == y[k + 1]) ++k;
		printf(format, k);
		printf("\n");
	}
	return 0;
}

/*
3
4 5 3
3 5 4
2
1 1
3 3
*/
