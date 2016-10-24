/*
作者:千里冰封
题目:p2645 Spore
*/
#include <bits/stdc++.h>
#define size 10001
#define INF 0xfffff
#define ms(x, v) memset(x, v, sizeof(x))
int edge[size], to[size], head[size], next[size], d[1001], cnt[1001], m, n, idx;
bool inq[1001];
std::queue<int> q;
inline void addEdge(int fr, int _to, int val) {
	to[idx] = _to, edge[idx] = val, next[idx] = head[fr], head[fr] = idx++;
}
inline bool spfa(int s) {
	int i, j, k;
	for (i = 1; i <= n; ++i) d[i] = INF;
	while (!q.empty()) q.pop();
	q.push(s), ++inq[s], d[1] = 0;
	while (!q.empty()) {
		i = q.front(), q.pop();
		inq[i] = false;
		for (j = head[i]; ~j; j = next[j]) {
			k = to[j];
			if (d[k] > d[i] + edge[j]) {
				d[k] = d[i] + edge[j];
				if (!inq[k]) {
					inq[k] = true;
					q.push(k);
					if (cnt[k] > n) return true;
				}
			}
		}
	}
	return false;
}

int main(int argc, char *argv[]) {
	int i, j, g1, g2, c1, c2;
	q = *new std::queue<int>;
	while (scanf("%i %i", &n, &m) != EOF) {
		if (!n && !m) break;
		ms(head, -1), ms(next, -1), ms(inq, false), ms(cnt, 0);
		for (i = 0; i < m; ++i) scanf("%i %i %i %i", &g1, &g2, &c1, &c2),
			    addEdge(g1, g2, c1), addEdge(g2, g1, c2);
		if (spfa(1) || d[n] > (INF >> 2)) puts("No such path");
		else printf("%i\n", d[n]);
	}
	return 0;
}

/*
3 2 1 2 2 -1 2 3 0 1 0 0
*/

