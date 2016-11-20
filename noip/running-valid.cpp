#include <stdio.h>
#include <string.h>

#define size 300010
#define int long long

inline int read() {
  int i = 0, p = 1, c = getchar();
  while (c < '0' || c > '9') { if (c == '-') p = -1; c = getchar(); }
  while (c >= '0' && c <= '9') i = (i * 10) + c - '0', c = getchar();
  return i;
}

int tsw[size], head[size], next[size], mark[size];
int past[size], die[size];
///            begin num
int lly[size], lyj[size], lsw, yzh, ans;
int head2[size], next2[size];
/// time num

void dfs(int root, int depth) {
  int i, j;
  ++depth;
  for (i = head[root]; ~i; i = next[i]) {
    for (j = head2[root]; ~j; j = next2[j]) {
      past[];
      ++die[j];
    }
    dfs(tsw[i], depth);
  }
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long

  freopen("running.in", "r", stdin);
  freopen("running.out", "w", stdout);
  int i, j, k, root;
  memset(head, -1, sizeof(head));
  memset(head2, -1, sizeof(head2));
  memset(next, -1, sizeof(next));
  memset(next2, -1, sizeof(next2));
  lsw = read();
  yzh = read();
  for (i = 0; i < lsw - 1; ++i) {
    j = read();
    tsw[i] = read();
    ++mark[tsw[i]];
    next[i] = head[j];
    head[j] = i;
  }
  for (i = 0; i < lsw - 1; ++i) {
    if (!mark[i]) break;
  }
  memset(mark, 0, sizeof(mark));
  root = i;
  for (i = 0; i < lsw; ++i) {
    lly[i] = read();
  }
  for (i = 0; i < yzh; ++i) {
    j = read();
    lyj[j] = read();
    next2[i] = head2[j];
    head2[j] = i;
  }
  const int beginDepth = 0;
  past[beginDepth][0] = tsw[root];
  dfs(root, beginDepth);
  return 0;
}
