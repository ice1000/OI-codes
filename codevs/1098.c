/*
作者:千里冰封
题目:p1098 均分纸牌
*/

#include <stdio.h>
#include <math.h>

int a[1001], n, avg, tot;

int main(int argc, char *argv[]) {
  int i;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
    tot += a[i];
  }
  avg = tot / n;
  tot = 0;
  for (i = 0; i < n - 1; ++i) {
    a[i + 1] += a[i] - avg;
    if (avg - a[i]) ++tot;
  }
  printf("%i", tot);
  return 0;
}

