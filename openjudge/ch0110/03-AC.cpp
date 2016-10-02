#include <stdio.h>
#include <algorithm>

struct ass {
  int s;
  char name[20];
  bool operator<(const ass& o) const {
    if (s ^ o.s) return s < o.s;
    int i = 0;
    do {
      if (name[i] ^ o.name[i]) return name[i] > o.name[i];
    } while (++i <= 20);
  }
} a[10001];

int main(int argc, char *argv[]) {
  int n, i;
  scanf("%i", &n);
  for (i = 0; i < n; ++i) scanf("%s %i", a[i].name, &a[i].s);
  std::sort(a, a + n);
  for (i = n - 1; i >= 0; --i) printf("%s %i\n", a[i].name, a[i].s);
  return 0;
}
/**
4
Kitty 80
Hanmeimei 90
Joey 92
Tim 28
*/

