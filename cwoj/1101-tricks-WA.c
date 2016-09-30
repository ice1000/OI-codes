#include <stdio.h>
#include <iostream>
#include <algorithm>

long long a[10001], n, k, m;
long long s[100], mark[100];

void dfs(int v, int step, int max) {
  a[m++] = v;
  int i;
  for (i = max - 1; i >= 0; --i) {
    if (!mark[i]) {
      ++mark[i];
      dfs(v + s[i], step, i);
      --mark[i];
    }
  }
}

int main(int argc, char *argv[]) {
  int i, j;
  std::cin >> k >> n;
  s[0] = 1;
  for (i = 1; i < 30; ++i)
//  std::cout<<" "<<
  (s[i] = s[i - 1] * k);
  dfs(0, 0, 12);
  std::sort(a, a + m);
//  for (i = 1; i < m; ++i) printf("%I64d ", a[i]);
  std::cout << a[n] << std::endl;
  return 0;
}
