#include <stdio.h>
#include <queue>

using std::queue;

int n, m, begin, end;
int speed[201][201];

typedef struct node {
  int p;
  int min;
  int step;
  node() {
    step = 0;
  }
  node(int _p) {
    p = _p;
    min = 0xfff;
    step = 0;
  }
  ~node() {}
} node ;

queue<node> *q;

int find(int l, int r) {
  if (l >= r) return l;
  int mid = (l + r) >> 1, i;
  bool found = false;
//  printf("<%i>==<%i>==<%i>\n", l, mid, r);
  while (!q->empty()) {
    q->pop();
  }
  node no(begin);
  q->push(no);
  while (!q->empty()) {
    no = (q->front());
//    printf("%i\n", no.p);
    q->pop();
    no.step++;
    if (no.p == end) {
      found = true;
      break;
    }
    if (no.step >= m) {
      delete &no;
      continue;
    }
    for (i = 1; i <= n; ++i) {
      if (speed[no.p][i] && speed[no.p][i] - no.min < mid) {
        no.p = i;
        if (speed[no.p][i] < no.min) {
          no.min = speed[no.p][i];
        }
        q->push(no);
      }
    }
  }
  if (found) return find(l, mid);
  else return find(mid + 1, r);
}

int main(int argc, char *argv[]) {
  freopen("road.in", "r", stdin);
//  freopen("road.out", "w", stdout);
  q = new queue<node>();
  int i, j, k, l, q, min = 0xffff, max = 0;
  while (scanf("%i %i", &n, &m) != EOF) {
    for (i = 1; i <= n; ++i) {
      for (j = 1; j <= n; ++j) {
        speed[i][j] = 0;
      }
    }
    for (i = 0; i < m; ++i) {
      scanf("%i %i %i", &l, &j, &k);
      speed[l][j] = k;
      speed[j][l] = k;
      if (k < min) {
        min = k;
      }
      if (k > max) {
        max = k;
      }
    }
    scanf("%i", &q);
//    printf("q = %i\n", q);
    for (i = 0; i < q; ++i) {
      scanf("%i %i", &begin, &end);
      printf("%i\n", find(0, max - min));
    }
  }
  return 0;
}

