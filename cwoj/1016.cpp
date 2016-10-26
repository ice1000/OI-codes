#include <bits/stdc++.h>
#define INF 0xfffffff
#define ms(x, y) memset(x, y, sizeof(x))

const char *fail = "Trapped in loop!";
int n, head[5001], next[5001], value[5001], to[5001];
int d[5001], inq[5001], visit[5001], idx = 0;

inline bool spfa(int s) {
  std::queue<int> q = *new std::queue<int>;
  int i, j, v;
  while (!q.empty()) q.pop();
  for (i = 1; i <= n; ++i) d[i] = INF;
  q.push(s), ++inq[s], d[s] = 0;
  while (!q.empty()) {
    i = q.front(), q.pop();
    if (++visit[i] >= n) return true;
    for (j = head[i]; ~j; j = next[j]) {
      v = to[j];
      if (d[v] > d[i] + value[j]) {
        d[v] = d[i] + value[j];
        if (!inq[v]) ++inq[v], q.push(v);
      }
    }
    inq[i] = 0;
  }
  return false;
}

int main(int argc, const char *argv[]) {
  int i, j, k, l, m;
  ms(head, -1), ms(next, -1), ms(visit, 0);
  scanf("%i %i", &n, &m);
  for (i = 0; i < m; ++i) {
    scanf("%i %i %i", &j, &to[i], &value[i]);
    next[i] = head[j];
    head[j] = i;
  }
  if (spfa(1) || d[n] < 0) {
    printf(fail);
  } else {
    printf("%i", d[n]);
  }
  return 0;
}

/*
3 3
1 2 1
2 3 1
3 1 1
*/

