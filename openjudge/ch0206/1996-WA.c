/*
作者:千里冰封
题目:p1058 合唱队形
*/

#include <stdio.h>
#include <string.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int a[2001], n, dp1[2001], dp2[2001], m = 0, mm = 0;

int find1(int l, int r, int n) {
  if (l >= r) return l;
  int mid = (l + r) / 2;
  return dp1[mid] == n ? mid : dp1[mid] > n ? find1(l, mid, n) : find1(mid + 1, r, n);
}

int find2(int l, int r, int n) {
  if (l >= r) return l;
  int mid = (l + r) / 2;
  return dp2[mid] == n ? mid : dp2[mid] > n ? find2(l, mid, n) : find2(mid + 1, r, n);
}

int main(int argc, char *argv[]) {
  int i, j;
  scanf("%i", &n);

  for (i = 0; i < n; ++i) {
    scanf("%i", &a[i]);
    dp1[i] = 1;
    dp2[i] = 1;
  }

  for (i = 0; i < n; ++i) {
    if (a[i] < dp1[m]) dp1[++m] = a[i];
    else dp1[find1(0, m, a[i])] = a[i];
  }

  for (i = n - 1; i >= 0; --i) {
    if (a[i] < dp2[mm]) dp2[++mm] = a[i];
    else dp2[find2(0, mm, a[i])] = a[i];
  }

  printf("%i", max(m, mm));

  return 0;
}
/**
8
186 186 150 200 160 130 197 220
*/

