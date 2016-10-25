#include <stdio.h>
#include <string.h>

#define foreach(i, f, t) for(i = f; i < t; ++i)
#define foreach_down(i, f, t) for(i = f - 1; i >= t; --i)
#define size 1000005

int a[size + 10], max = 1;

void exe(int n) {
  int i;
  foreach(i, 0, max) {
    if (a[i]) {
      a[i] *= n;
    }
  }
  foreach(i, 0, max) {
    if (a[i] >= 10) {
      if (i == max) ++max;
      a[i + 1] += a[i] / 10;
      a[i] %= 10;
    }
  }
}

int main(int argc, const char *argv[]) {
  int i, n, started = 0;
  scanf("%i", &n);
  memset(a, 0, sizeof(a));
  a[0] = 1;
  foreach(i, 0, n) {
    exe(i + 1);
  }
//  foreach_down(i, size, 0) {
//    if (started || a[i]) {
//      if (!started) ++started;
////      printf("[%i] %i\n", i, a[i]);
//      printf("%i", a[i]);
//    }
//  }
  foreach_down(i, max, 0) {
    printf("%i", a[i]);
  }
}
