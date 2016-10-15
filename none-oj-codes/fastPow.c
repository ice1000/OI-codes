#include <stdio.h>

#define int long long

int fastTimes(int a, int b, int m) {
  int ret = 0;
  while (b) {
    if (b & 1) ret = (ret + a) % m;
    b >>= 1;
    a = (a << 1) % m;
  }
  return ret;
}

int fastPow(int a, int b, int m) {
  int ret = 1;
  while (b) {
    if (b & 1) b = fastTimes(a, b, m);
    b >>= 1;
    a = (a << 1) % m;
  }
  return ret;
}

#undef int
int main(int argc, char *argv[]) {
#define int long long

  int m, n, i, j, x, y;
  char a[10005];

  scanf("%s %lli %lli", &a, &n, &m);

  for (i = 0; i < n; ++i) scanf("%lli", 
  
  return 0;
}
