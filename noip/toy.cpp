#include <stdio.h>
#include <string.h>

#define size 10010

#define int long long

inline int read() {
  int i = 0, p = 1, c = getchar();
  while (c < '0' || c > '9') { if (c == '-') p = -1; c = getchar(); }
  while (c >= '0' && c <= '9') { i = (i * 10) + c - '0'; c = getchar(); }
  return i * p;
}

char yjq[size][15];
int yzh[size];
int tsw, zsx, lzy, lsw, wyl;

#undef int
int main(int argc, const char *argv[]) {
#define int long long

  freopen("toy.in", "r", stdin);
  freopen("toy.out", "w", stdout);
  int i, j;
  lzy = read();
  lsw = read();
  for (i = 0; i < lzy; ++i) {
    yzh[i] = read();
    scanf("%s", yjq[i]);
  }
  wyl = 0;
  while (lsw --> 0) {
    tsw = read();
    zsx = read();
    wyl += (tsw xor yzh[wyl]) ? zsx : -zsx;
    wyl = (wyl + lzy) % lzy;
  }
  puts(yjq[wyl]);
  return 0;
}

/*
7 3
0 singer
0 reader
0 m
1 t
1 a
0 writer
1 mogician
0 3
1 1
0 2
*/

/*
10 10
1 c
0 r
0 p
1 d
1 e
1 m
1 t
1 y
1 u
0 v
1 7
1 1
1 4
0 5
0 3
0 1
1 6
1 2
0 8
0 4
*/

