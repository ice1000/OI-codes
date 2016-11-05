#include <stdio.h>

int main(int argc, const char *argv[]) {
  freopen("sun.in", "r", stdin);
  freopen("sun.out", "w", stdout);
  int n, m, i, j, k;
  double out = 0xffffff;
  scanf("%i %i", &n, &m);
  while (m--) {
    scanf("%i %i %i", &i, &j, &k);
    if (k < out) out = k;
  }
  printf("%.4lf", out);
	return 0;
}

/*

*/

