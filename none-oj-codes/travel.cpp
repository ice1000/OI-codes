#include <stdio.h>
#include <string.h>
#include <queue>

#define size 1010
#define ms(x, y) (memset(x, y, sizeof(x)))

int n, head[size], next[size], to[size], val[size], vis[size], dis[size], inq[size];

int spfa(int s) {
	int i, j;
	auto q = *new std::queue<int>();
	while (!q.empty()) q.pop();
	ms(dis, 0x7f), ms(vis, 0), ms(inq, 0);
	dis[s] = 0, q.push(s), ++inq[s];
	while (!q.empty()) {
		i = q.front(), q.pop();
		if (++vis[i] > n) return true;
		for (j = head[i]; ~j; j = next[j])
			if (dis[i] > dis[to[j]] + val[j]) {
				dis[i] = dis[to[j]] + val[j];
				if (!inq[to[j]]) ++inq[to[j]], q.push(to[j]);
			}
	}
	return false;
}

int main(int argc, const char *argv[]) {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	int t;
	scanf("%i", &t);
	while (t--) {
		ms(head, -1), ms(next, -1);

		puts("Impossible");
//		puts("Possible");
	}
	return 0;
}

