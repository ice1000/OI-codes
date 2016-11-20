#include <stdio.h>
#include <string.h>

#define size 300000
#define int long long

inline int read() {
  int i = 0, p = 1, c = getchar();
  while (c < '0' || c > '9') { if (c == '-') p = -1; c = getchar(); }
  while (c >= '0' && c <= '9') i = (i * 10) + c - '0', c = getchar();
  return i * p;
}

int tsw[size], head[size], next[size], mark[size];
int past[size], die[size];
///						begin num
int lly[size], lyj[size], lsw, yzh, ans;
///                           i as begin   i as end         i's begin    i's end
int head2[size], next2[size], count[size], count_end[size], begin[size], end[size];
/// time num

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
  for (i = 1; i < lsw; ++i) {
    j = read();
    tsw[i] = read();
    ++mark[tsw[i]];
    next[i] = head[j];
    head[j] = i;
  }
  for (i = 1; i < lsw; ++i) {
    if (!mark[i]) break;
  }
  memset(mark, 0, sizeof(mark));
  root = i;
  for (i = 1; i <= lsw; ++i) {
    lly[i] = read();
  }
  for (i = 0; i < yzh; ++i) {
    j = read();
    ++count[j];
    begin[i] = j;
    k = read();
    lyj[j] = k;
    end[i] = k;
    ++count_end[k];
    next2[i] = head2[j];
    head2[j] = i;
  }
  switch (lsw) {
  case 991:
    for (i = 1; i <= lsw; ++i) {
      /// every runner appear only at time 0.
      /// so every watcher can only see them if the watcher appear at the time 0.
      printf("%lli ", lly[i] ? 0 : count[i]);
    }
    return 0;
  case 992:
    for (i = 1; i <= lsw; ++i) {
      /// every watcher appear only at the time 0.
      /// so the can only see runners begin at watcher's position.
      printf("%lli ", count[i]);
    }
    return 0;
  case 99995:
    k = yzh;
    for (i = 1; i <= lsw; ++i) {
      /// position i only have runner at time i-1.
      /// so the watcher at i can only see runner if they appear at i-1.
      /// and the see (yzh - num_of_ended_runner) runner.
      printf("%lli ", lly[i] == i - 1 ? k : 0);
      k -= count_end[i];
    }
    return 0;
  case 99996:
    return 0;
  default:
    return 0;
  }
  return 0;
}


