/*
作者:千里冰封
题目:p1057 津津的储蓄计划
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, j, n = 0, m = 0;
  for (i = 0; i < 12; ++i) {
    scanf("%i", &j);
    n += 300 - j;
    if (n < 0) {
      printf("-%i", ++i);
      return 0;
    }
    m += n / 100;
    n %= 100;
  }
  printf("%i", m * 120 + n);
  return 0;
}

/*
290
230
280
200
300
170
340
50 
90 
80 
200
60

290
230
280
200
300
170
330
50
90
80
200
60
*/
