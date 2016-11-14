#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> van[100010];

int main(int argc, const char *argv[]) {
  int n, i, j;
  char command[1001];
  scanf("%i", &n);
  while (n --> 0) {
    scanf("%s", command);
    switch (command[0]) {
    case 'n':
      scanf("%i", &i);
      van[i] = *new vector<int>();
      break;
    case 'u':
      scanf("%i", &i);
      sort(van[i].begin(), van[i].end());
      van[i].erase(unique(van[i].begin(),
                          van[i].end()),
                   van[i].end());
      break;
    case 'a':
      scanf("%i %i", &i, &j);
      van[i].push_back(j);
      break;
    case 'm':
      scanf("%i %i", &i, &j);
      van[i].insert(van[i].end(),
                    van[j].begin(),
                    van[j].end());
      van[j].clear();
      break;
    case 'o':
      scanf("%i", &i);
      sort(van[i].begin(), van[i].end());
      for (j = 0; j < van[i].size(); ++j) {
        printf("%i ", van[i][j]);
      }
      putchar('\n');
      break;
    }
  }
  return 0;
}
