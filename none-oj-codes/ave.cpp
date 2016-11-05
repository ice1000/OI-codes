#include <queue>
#include <stdio.h>

#define INF 0xffffff

typedef struct node {
  double value;
  node(double _v = INF) : value(_v) {  }
  const bool operator<(const node& o) const {
    return value < o.value;
  }
} node;

long long a[200010 << 1];

int main(int argc, const char *argv[]) {
  freopen("ave.in", "r", stdin);
  freopen("ave.out", "w", stdout);
  int i, j, n, k;
  std::priority_queue<node> q = *new std::priority_queue<node>();
  scanf("%i %i", &n, &k);
  if (k == 1) {
    double min = INF;
    for (i = 1; i <= n; ++i) {
      scanf("%i", &j);
      if (j < min) min = j;
    }
    printf("%.4lf", min);
    return 0;
  }
  for (i = 1; i <= n; ++i) {
    scanf("%i", &j);
    a[i] = a[i - 1] + j;
    for (j = 0; j < i; ++j) {
      q.push(*new node((a[i] * 1.0 - a[j]) / (i - j)));
      if (q.size() > k) q.pop();
    }
  }
  printf("%.4lf", q.top());
	return 0;
}

/*
6 10 3 5 4 6 1 2
*/

