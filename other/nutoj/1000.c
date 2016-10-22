#include <stdio.h>

int main(int argc, char *argv[]) {
  int i, j;
  while (scanf("%i %i", &i, &j)) {
    if (!i && !j) break;
    printf("%i\n", i + j);
  }
  return 0;
}
