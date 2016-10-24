/*
作者:千里冰封
题目:p2602 最短路径问题
*/

#include <bits/stdc++.h>
using std::queue;
#define INF 0xfffffff
#define squared(x) ((x) * (x))

double a[1005][1005], d[1005];
int x[1005], y[1005], inq[1005], head[1005];
double distance (int a, int b) {
  return sqrt(squared(x[a] - x[b]) + squared(y[a] - y[b]));
}

struct Edge {
  int to, next;
  double w;
  Edge(): next(-1) { }
  Edge(int _to, double _w, int _next = -1): to(_to), w(_w), next(_next) { }
} es[1001];

int main (int argc, char *argv[]) {
  int n, m, i, j, k, l, fr, en, u, v;
  double w;
  queue<int> *q = new queue<int>();
  memset(head, -1, sizeof(head));
  memset(inq, 0, sizeof(inq));
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
    i = q->front(), q->pop();
    for (j = head[i]; ~j; j = es[j].next) {
      v = es[j].to;
      w = es[j].w;
      if (d[i] + w < d[v]) {
        d[v] = d[i] + w;
        if (!inq[v]) ++inq[v], q->push(v);
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
