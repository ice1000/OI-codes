/*
作者:千里冰封
题目:p2645 Spore
*/
#include <bits/stdc++.h>
#define INF 0xfffff
#define ms(x, v) memset(x, v, sizeof(x))
struct shit {
	int val, to;
	shit(int _val = 0, int _to = 0) : val(_val), to(_to) { }
} k ;
int d[1001], cnt[1001];
bool inq[1001];
std::queue<int> q;
std::vector<shit> fuck[1001];
int m, n, idx;
inline void addEdge(int fr, int _to, int val) {
	fuck[fr].push_back(*new shit(val, _to));
}

inline bool spfa(int s) {
	int i, j;
	for (i = 1; i <= n; ++i) d[i] = INF;
	q.push(s), ++inq[s], d[s] = 0;
	while (!q.empty()) {
		i = q.front(), q.pop();
		if (++cnt[k.to] > n) return true;
		for (j = 0; j < fuck[i].size(); ++j) {
			k = fuck[i][j];
			if (d[k.to] > d[i] + k.val) {
				d[k.to] = d[i] + k.val;
				if (!inq[k.to]) {
					inq[k.to] = true;
					q.push(k.to);
				}
			}
		}
		inq[i] = false;
	}
	return false;
}

int main(int argc, char *argv[]) {
	int i, j, g1, g2, c1, c2;
	while (scanf("%i %i", &n, &m) != EOF) {
		if (!n && !m) break;
		ms(inq, false), ms(cnt, 0);
		while (!q.empty()) q.pop();
		for (i = 1; i <= n; ++i) fuck[i].clear();
		for (i = 0; i < m; ++i) scanf("%i %i %i %i", &g1, &g2, &c1, &c2),
			    addEdge(g1, g2, c1), addEdge(g2, g1, c2);
		if (spfa(1) || d[n] > (INF >> 2)) puts("No such path");
		else printf("%i\n", d[n]);
//		for (i = 1; i <= n; ++i) printf("<%i>", d[i]);
//		putchar('\n');
	}
	return 0;
}

/*
3 2 1 2 2 -1 2 3 0 1 0 0

3 3
1 2 4 4
1 3 2 2
2 3 3 -3
3 3
1 2 4 4
1 3 2 2
2 3 -3 3
3 3
1 2 4 4
1 3 2 2
2 3 3 3
0 0
*/
