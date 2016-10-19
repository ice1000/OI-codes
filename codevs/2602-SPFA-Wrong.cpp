/*
  作者:千里冰封
  题目:p2602 最短路径问题
*/

#include <bits/stdc++.h>
using std::queue;
#define INF 0xfffffff
#define squared(x) ((x) * (x))

double a[105][105], d[105];
int x[105], y[105], inq[105], next[105], head[105];
double distance (int a, int b) {
  return sqrt(squared(x[a] - x[b]) + squared(y[a] - y[b]));
}

struct Edge {
  int to, next;
  double w;
  Edge() { }
  Edge(int _to, double _w, int _next): to(_to), w(_w), next(_next) { }
  ~Edge() { }
} es[1001];

int main (int argc, char *argv[]) {
  int n, m, i, j, k, l, fr, en, u, v;
  queue<int> *q = new queue<int>();
  memset(head, -1, sizeof(head));
  memset(next, -1, sizeof(next));
  scanf("%i", &n);
  for (i = 1; i <= n; ++i) scanf("%i %i", &x[i], &y[i]), d[i] = INF;
  scanf("%i", &m);
  for (l = i = 0; i < m; ++i) {
    scanf("%i %i", &j, &k);
    es[l] = *new Edge(k, distance(j, k), head[j]);
    head[j] = l++;
    es[l] = *new Edge(j, distance(k, j), head[k]);
    head[k] = l++;
  }
  /* SPFA */
  scanf("%i %i", &fr, &en);
  inq[fr] = 1;
  d[fr] = 0;
  while (!q->empty()) q->pop();
  q->push(fr);
  ++inq[fr];
  while (!q->empty()) {
    i = q->front();
    q->pop();
    inq[i] = 0;
    for (j = head[i]; j != -1; j = next[j]) {
      v = es[j].to;
      if (d[i] + es[j].w < d[v]) {
        d[v] = d[i] + es[j].w;
        if (!inq[v]) {
          ++inq[v];
          q->push(v);
        }
      }
    }
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

