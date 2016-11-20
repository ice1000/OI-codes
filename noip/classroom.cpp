#include <stdio.h>
#include <string.h>

#define size 1010

inline int read() {
  int i = 0, p = 1, c = getchar();
  while (c < '0' || c > '9') { if (c == '-') p = -1; c = getchar(); }
  while (c >= '0' && c <= '9') i = (i * 10) + c - '0', c = getchar();
  return i * p;
}

int n, m, v, e;
int course[size], course2[size];
int map[size][size];
double prob[size];

int main(int argc, const char *argv[]) {
	freopen("classroom.in", "r", stdin);
	freopen("classroom.out", "w", stdout);
  int i, j, k, a = 0xfffff, b = 0xfffff;
	double ans = 0;
  n = read();
  m = read();
  v = read();
  e = read();
  memset(map, 0x7f, sizeof(map));
  for (i = 1; i <= n; ++i) {
  	course[i] = read();
  }
  for (i = 1; i <= n; ++i) {
  	course2[i] = read();
  }
  for (i = 1; i <= n; ++i) {
  	scanf("%lf", &prob[i]);
  }
  while (e --> 0) {
  	i = read();
  	j = read();
  	map[i][j] = read();
  	if (map[i][j] > map[j][i]) map[i][j] = map[j][i];
  	else map[j][i] = map[i][j];
  }
  for (k = 1; k <= n; ++k) {
  	for (i = 1; i <= n; ++i)
  		for (j = 1; j <= n; ++j)
  			if (map[i][j] > map[i][k] + map[k][j])
  				map[i][j] = map[i][k] + map[k][j];
  }
  for (i = 2; i <= n; ++i) {
  	j = map[course[i - 1]][course[i]];
  	ans += j;
  }
  switch (m) {
	case 0:
		printf("%.2lf", ans);
		break;
	case 1:
		break;
	case 2:
		break;
  }
  return 0;
}

