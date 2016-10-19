/*
作者:千里冰封
题目:p1039 数的划分
*/

#include <stdio.h>

int f(int a, int b, int c) {
  if(a == b * c || a == b * c + 1 || b == 1) return 1;
  int sum = 0, i;
  for(i = c; i <= a / b; ++i) sum += f(a - i, b - 1, i);
  return sum;
}

int main(int argc, char *argv[]) {
  int a, b;
  scanf("%i %i", &a, &b);
  printf("%i", f(a, b, 1));
}

