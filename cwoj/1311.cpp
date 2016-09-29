#include <stdio.h>
#include <algorithm>
#include <iostream>
const char *fail = "Loowater is doomed!\n";
long long a[20001], b[20001];
int main(int argc, char *argv[]) {
  long long i, j, n, m, tot = 0, f = 0;
  while (1) {
    tot = 0;
    f = 0;
    std::cin>>n>>m;
    if (!n and !m) break;
    for (i = 0; i < n; ++i) std::cin>>a[i];
    for (i = 0; i < m; ++i) std::cin>>b[i];
    std::sort(a, a + n);
    std::sort(b, b + m);
    for (i = 0, j = 0; i < n; ) {
      if (j >= m) ++f, break;
      if (a[i] <= b[j]) {
	tot += b[j];
	++i;
      }
      ++j;
    }
    if (f) printf(fail);
    else std::cout<<tot<<"\n";
  }
  return 0;
}

/**
2 3
5
4
7
8
4
2 1
5
5
10
0 0
*/
