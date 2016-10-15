#include <stdio.h>
#include <queue>

#define INF 0xffff

#ifdef __min
#undef __min
#endif

#ifdef __max
#undef __max
#endif

#define __min(x, y) ((x) < (y) ? (x) : (y))
#define __max(x, y) ((x) > (y) ? (x) : (y))

using std::queue;

struct Node2 {
  int d, u;
  Node2() {
  }
  Node2(int _d, int _u) : d(_d), u(_u) {
  }
  ~Node2() {
  }
};

struct Edge {
  int w, u, v, next;
  Edge() {
  }
  Edge(int _u, int _v, int _w, int _n): w(_w), u(_u), v(_v), next(_n) {
  }
  ~Edge() {
  }
  void read() {
    scanf("%i %i %i", &u, &v, &w);
  }
} es[1001];

bool inq[1001];
int n, m, d[1001], vc[1001];
int head[1001], esc = 0;
queue<Node2> *q;

void addEdge(int u, int v, int w) {
  es[esc] = *(new Edge(u, v, w, head[u]));
  head[u] = esc++;
}

bool spfa(int s) {
  int i, e;
  for (i = 0; i < n; ++i) {
    inq[i] = i == s;
    d[i] = inq[i] ? 0 : INF;
    vc[i] = 0;
  }
  q = new queue<Node2>();
  while (!q->empty()) {
    q->pop();
  }
  Node2 *no = (new Node2());
  q->push(*no);
  while (!q->empty()) {
    no = &q->front();
    q->pop();
    inq[no->u] = false;
    if (vc[no->u]++ > n) {
      return false;
    }
    for (e = head[no->u]; e != INF; e = es[e].next) {
      if (d[no->u] + es[e].w > d[es[e].v]) {
        d[es[e].v] = d[no->u] + es[e].w;
        if (!inq[es[e].v]) {
          inq[es[e].v] = true;
          q->push(*(new Node2(d[es[e].v], es[e].v)));
        }
      }
    }
  }
  
  return false;
}

int main(int argc, char *argv[]) {
  int i, j, u, v, w;
  scanf("%i %i", &n, &m);
  for (i = 0; i < m; ++i) {
    scanf("%i %i %i", &u, &v, &w);
    addEdge(u, v, w);
  }
  spfa(1);
//  printf
  return 0;
}
