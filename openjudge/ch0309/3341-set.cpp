#include <stdio.h>
#include <set>

using namespace std;

int main(int argc, const char *argv[]) {
  int n, i, j;
  char a[11];
  set<int> deep = *new set<int>();
  set<int> his = *new set<int>();
  scanf("%i", &n);
  while (n --> 0) {
    scanf("%s %i", a, &i);
    switch (a[1]) {
    case 'd':
      deep.insert(i);
      his.insert(i);
      printf("%i\n", deep.count(i));
      break;
    case 'e':
      printf("%i\n", deep.count(i));
      deep.erase(i);
      break;
    case 's':
      printf("%c %d\n", his.count(i) ? '1' : '0', deep.count(i));
      break;
    }
  }
  return 0;
}
