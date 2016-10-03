#include <stdio.h>

char s[500];
int n, i, loestAAA = 0, numAAA = 0;
unsigned int now = 0, stack = 0;

inline void judge() {
  if (!stack && now > loestAAA) loestAAA = now;
  if (now && stack > 0) ++numAAA;
  now = 0;
}

int main (int argc, char *argv[]) {
  scanf("%i %s", &n, s);
  for (i = 0; i < n; ++i) {
    switch (s[i]) {
    case '(':
      judge();
      ++stack;
      break;
    case ')':
      judge();
      --stack;
      break;
    case '_':
      judge();
      break;
    default:
      ++now;
      break;
    }
  }
  judge();
  printf("%i %i", loestAAA, numAAA);
  return 0;
}




