/*
作者:千里冰封
题目:p1073 家族
*/

#include <stdio.h>

int a[100001], n;

int find(int i) {
  if (a[i] != i) return find(a[i]);
  return i;
}

void merge(int i, int j) {
  i = find(i);
  j = find(j);
  if (i - j) a[i] = a[j];
}

int main(int argc, char *argv[]) {
  int i, j, k, m, p;
  scanf("%i %i %i", &n, &m, &p);
  for (i = 0; i < n; ++i) a[i] = i;
  for (i = 0; i < m; ++i) {
    scanf("%i %i", &j, &k);
    merge(j, k);
  }
  for (i = 0; i < p; ++i) {
    scanf("%i %i", &j, &k);
    printf(find(j) - find(k) ? "No\n" : "Yes\n");
  }
  return 0;
}
