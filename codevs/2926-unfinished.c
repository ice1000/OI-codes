#include <stdio.h>
int a[9][9], hash[9][9], mark[9][9], num;
int get(int bit) {
  int i = 0;
  while (++i)
    if (bit & 1) return i;
}
int main(int argc, char *argv[]) {
  int i, j, m, n, x, y, k, l;
  for (i = 0; i < 9; ++i)
    for (j = 0; j < 9; ++j) {
      scanf("%i", &a[i][j]);
      hash[i][j] = ((1 << 10) - 1) ^ (a[i][j] ? (1 << (a[i][j] - 1)) : 0);
      if (!a[i][j]){
	++num;
	++mark[i][j];
      }
    }
  while (num) {
    for (m = 0; m < 3; ++m)
      for (n = 0; n < 3; ++n){
	for (i = 0; i < 3; ++i)
	  for (j = 0; j < 3; ++j){
	    x = m + m + m + i;
	    y = n + n + n + j;
	    if (!mark[x][y])
	      for (k = 0; k < 9; ++k)	{
		if (mark[x][k]) hash[x][k] ^= (1 << (a[x][y] - 1));
		if (mark[k][y]) hash[k][y] ^= (1 << (a[x][y] - 1));
	      }
	  }
	
      }
  }
  for (i = 0; i < n; ++i) {
    for (j = 0; j < 9; ++j)
      printf("%i ", a[i][j]);
    printf("\n");
  }
  return 0;
}
