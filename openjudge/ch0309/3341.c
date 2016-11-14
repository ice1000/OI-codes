#include <stdio.h>

int his[5000010];
int tot[5000010];

int main(int argc, const char *argv[]) {
  int n, i, j;
  char a[11];
  scanf("%i", &n);
  while (n --> 0) {
    scanf("%s %i", a, &i);
    switch (a[1]) {
    case 'd':
      ++his[i];
      ++tot[i];
      printf("%i\n", tot[i]);
      break;
    case 'e':
      printf("%i\n", tot[i]);
      tot[i] = 0;
      break;
    case 's':
      printf("%c %d\n", his[i] ? '1' : '0', tot[i]);
      break;
    }
  }
  return 0;
}
