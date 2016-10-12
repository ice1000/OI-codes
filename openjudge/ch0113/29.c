#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int i, j, n, mark[30], max = -1;
  char a[1001];
  memset(mark, 0, 30 * sizeof(int));
  scanf("%s", a);
  for (i = 0; i < strlen(a); ++i) {
    ++mark[a[i] - 'a'];
  }
  for (i = 0; i < 26; ++i) {
    if (mark[i] > mark[max]) {
      max = i;
    }
  }
  printf("%c %i", max + 'a', mark[max]);
  return 0;
}

