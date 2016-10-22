#include <stdio.h>

char pro(char a) {
  if (a == 'J') a = '9' + 1;
  if (a == 'Q') a = '9' + 2;
  if (a == 'K') a = '9' + 3;
  if (a == 'A') a = '1';
  return a;
}

int main(int argc, char *argv[]) {
  int t;
  char a, b, x, y, k;
  scanf("%i", &t);
  while (t--) {
    getchar();
    k = getchar();
    getchar();
    a = getchar();
    a = pro(a);
    x = getchar();
    getchar();
    b = getchar();
    b = pro(b);
    y = getchar();
    if (x == k) {
      puts("YES");
    } else if (y == k) {
      puts("NO");
    } else if (a > b) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}
