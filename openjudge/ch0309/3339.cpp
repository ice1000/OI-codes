#include <stdio.h>
#include <algorithm>
#include <list>

using namespace std;

list<int> van[100010];

int main(int argc, const char *argv[]) {
  int n, i, j;
  char command[1001];
  scanf("%i", &n);
  while (n --> 0) {
    scanf("%s", command);
    switch (command[0]) {
    case 'n':
      scanf("%i", &i);
      van[i] = *new list<int>();
      break;
    case 'u':
      scanf("%i", &i);
      van[i].sort();
      van[i].unique();
      break;
    case 'a':
      scanf("%i %i", &i, &j);
      van[i].push_back(j);
      break;
    case 'm':
      scanf("%i %i", &i, &j);
      van[i].merge(van[j]);
      break;
    case 'o':
      scanf("%i", &i);
      van[i].sort();
      for (auto j = van[i].begin(); j != van[i].end(); ++j) {
        printf("%i ", *j);
      }
      putchar('\n');
      break;
    }
  }
  return 0;
}
