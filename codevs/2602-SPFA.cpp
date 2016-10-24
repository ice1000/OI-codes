/*
作者:千里冰封
题目:p2602 最短路径问题
*/

#include <bits/stdc++.h>
#define INF 0xfffffff
#define squared(x) ((x) * (x))
#define ms(x, v) memset(x, v, sizeof(x))

double d[105];
int x[105], y[105], inq[105], cnt[105];
double distance (int a, int b) {
  return sqrt(squared(x[a] - x[b]) + squared(y[a] - y[b]));
}

struct Edge {
  int to;
  double w;
  Edge(int _to = 0, double _w = 0): to(_to), w(_w) { }
} e;

int main (int argc, char *argv[]) {
  int n, m, i, j, k, l, fr, en, u, v;
  std::queue<int> *q = new std::queue<int>();
  std::vector<Edge> vec[105];
  ms(inq, 0), ms(cnt, 0);
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) scanf("%i %i", &x[i], &y[i]), d[i] = INF;
  scanf("%i", &m);
  for (l = i = 0; i < m; ++i) {
    scanf("%i %i", &j, &k);
    vec[j].push_back(*new Edge(k, distance(j, k)));
    vec[k].push_back(*new Edge(j, distance(k, j)));
  }
  /* SPFA */
  scanf("%i %i", &fr, &en);
  inq[fr] = 1, d[fr] = 0;
  while (!q->empty()) q->pop();
  q->push(fr);
  ++inq[fr];
  while (!q->empty()) {
    i = q->front(), q->pop();
    if (++cnt[i] > n) break;
    for (j = 0; j < vec[i].size(); ++j) {
      e = vec[i][j];
      if (d[e.to] > d[i] + e.w) {
        d[e.to] = d[i] + e.w;
        if (!inq[e.to]) {
          ++inq[e.to];
          q->push(e.to);
        }
      }
    }
    inq[i] = 0;
  }
  printf("%.2lf\n", d[en]);
  return 0;
}
/*
5
0 0
2 0
2 2
0 2
3 1
5
1 2
1 3
1 4
2 5
3 5
1 5
*/

