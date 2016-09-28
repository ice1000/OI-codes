#include <stdio.h>

int p[101][101];
int out[101][2], idx = 0;

int main(int argc, char *argv[]) {
  int n, i, j, max = 0;
  scanf("%i", &n);
  while (n--) {
    scanf("%i %i", &i, &j);
    ++p[i][j];
  }
  for (i = 100; i >= 0; --i) {
    for (j = 100; j >= 0; --j) {
      if (j <= max) break;
      if (p[i][j] > 0) {
      	out[idx][0] = i;
      	out[idx++][1] = j;
      	max = j;
	break;
      }
    }
  }
  --idx;
  printf("(%i,%i)", out[idx][0], out[idx][1]);
  while (idx--) {
    printf(",(%i,%i)", out[idx][0], out[idx][1]);
  }
  return 0;
}

/**
5 1 2 2 2 3 1 2 3 1 4
*/
