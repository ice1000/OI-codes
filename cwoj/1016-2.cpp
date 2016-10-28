#include <stdio.h>
#include <string.h>
#include <queue>

#define ms(x, y) memset((x), (y), sizeof(x))
#define INF 0xfffffff
#define size 5001

int head[size], next[size], value[size], target[size], dis[size], visit[size],
    inq[size];
int m, n;

inline bool spfa(int s) {
	auto q = *new std::queue<int>;
	int i, j;
	for (i = 1; i <= n; ++i) dis[i] = INF;
	while (!q.empty()) q.pop();
	dis[s] = 0;
	q.push(s);
	++inq[s];
	while (!q.empty()) {
		i = q.front();
		q.pop();
		if (++visit[i] >= n) return true;
		for (j = head[i]; ~j; j = next[j]) {
			if (dis[target[j]] > dis[i] + value[j]) {
				dis[target[j]] = dis[i] + value[j];
				if (!inq[target[j]]) {
					++inq[target[j]];
					q.push(target[j]);
				}
			}
		}
		inq[i] = 0;
	}
	return false;
}

int main(int argc, char *argv[]) {
	int i, j;
	scanf("%i %i", &n, &m);
	ms(head, -1), ms(next, -1), ms(inq, 0), ms(visit, 0);
	for (i = 0; i < m; ++i) {
		scanf("%i %i %i", &j, &target[i], &value[i]);
		next[i] = head[j];
		head[j] = i;
	}
	if (spfa(1) or dis[n] < 0) printf("Trapped in loop!");
	else printf("%i", dis[n]);
	return 0;
}

