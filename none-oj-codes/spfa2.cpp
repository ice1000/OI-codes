#include <stdio.h>
#include <string.h>
#include <queue>

#define ms(x, y) memset(x, y, sizeof(x))
#define INF 0xfffff

int w[1001], to[1001], head[1001], next[1001], idx, inq[1001], d[1001];

void addEdge(int f, int t, int w) {
	w[idx] = w;
	to[idx] = t;
	next[idx] = head[f];
	head[f] = idx++;
}

bool spfa(int s) {
	int i, j, x, v;
	std::queue<int> q;
	while (!q.empty()) q.pop();
	for (i = 0; i <= n; ++i) d[i] = INF;
	q.push(s);
	++inq[s];
	d[s] = 0;
	while (!q.empty()) {
		i = q.front();
		q.pop();
//		if (++used[i]) return false;
		for (j = head[i]; ~j; j = next[j]) {
			if (d[to[j]] > w[j] + d[i]) {
				d[to[j]] = w[j] + d[i];
				if (!inq[j]) {
					++inq[j];
					q.push(j);
				}
			}
		}
		inq[i] = 0;
	}
	return true;
}

int main(int argc, const char *argv[]) {
  int n, i, j;
  scanf("%i", &n);
  ms(w, 0), ms(to, -1), ms(head, -1), ms(next, -1), ms(inq, 0), ms(d, 0);
  // add edges
  
  return 0;
}
