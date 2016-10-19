#include <stdio.h>

int main(int argc, char *argv[]) {
  int a[10001] = { 0, 3, 7, 17 }, i = 4, n, m;
  scanf("%lli", &n);
  m = n;
  /// 传说中的运算符——趋向于 
  while (n --> 3) {
    a[i] = a[i - 2] + (a[i - 1] << 1);
    a[i++] %= 12345;
  }
  printf("%lli", a[m]);
  return 0;
}
