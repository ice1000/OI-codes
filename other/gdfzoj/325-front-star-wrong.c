#include <stdio.h>
#include <string.h>

#define size 200001

/// front star
int to[size], head[size], next[size], n;

int main(int argc, char *argv[]) {
  int i, j, k, ans = 0;
  memset(next, -1, sizeof(next));
  memset(head, -1, sizeof(head));
  scanf("%i", &n);
  for (i = 0; i < n; ++i) {
    scanf("%i %i", &j, &k);
    to[i] = k;
    next[i] = head[j];
    head[j] = i;
  }
  for (i = 0; i < size; ++i) {
    if (~head[i]) {
      ++ans;
    }
    else {
      for (j = head[i]; ~j; j = next[j]) {
	//
      }
    }
  }
  return 0;
}
