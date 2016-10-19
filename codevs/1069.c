#include <stdio.h>

int fr[100001], to[100001], va[100001];
int uset[20001];
int n, m;

int find(int shit) {
  return uset[shit] == shit ? shit : (uset[shit] = find(uset[shit]));
}

void merge(int l, int r) {
  if (find(l) != find(r)) uset[l] = r;
}

int main(int argc, char *argv[]) {
  int i, j;
  scanf("%i %i", &n, &m);
  for (i = 0; i < m; ++i) {
    scanf("%i %i %i", &fr[i], &to[i], &va[i]);
    merge(fr[i], to[i]);
  }
  //
  return 0;
}
