#include <stdio.h>

int main(int argc, const char *argv[]) {
	freopen("paper.in", "r", stdin);
	freopen("paper.out", "w", stdout);
	int n, m, i, j, tmp, tot = 0;
  scanf("%i %i", &n, &m);
  for (i = 0; i < n; ++i) {
    for (j = 0; j < m; ++j) {
      scanf("%i", &tmp);
      if (tmp > 0) tot += tmp;
    }
  }
  printf("%i", tot);
	return 0;
}

