#include <stdio.h>
#include <queue>
const int INF = 0xffffff;
const int size = 100005;

long long n, m, head[size], next[size], value[size], target[size], inq[size], dis[size];
long long loosed[size], connected[size];

bool spfa(int s) {
	long long i, j;
	std::queue<long long> q = *new std::queue<long long>;
	while (!q.empty()) q.pop();
	for (i = 0; i <= n; ++i) dis[i] = INF;
	q.push(s);
	++inq[s];
	while (!q.empty()) {
		i = q.front();
		q.pop();
		for (j = head[i]; ~j; j = next[j]) {
			if (dis[target[j]] > value[j] + dis[i]) {
				dis[target[j]] = value[j] + dis[i];
				++loosed[j];
				if (!inq[target[j]]) ++inq[target[j]], q.push(target[j]);
			}
		}
		inq[i] = 0;
	}
}

int main(int argc, const char *argv[]) {
	long long i, j;
	scanf("%lli %lli", &n, &m);
	for (i = 0; i < m; ++i) {
		scanf("%lli %lli %lli", &j, &target[i], &value[i]);
		next[i] = head[j];
		head[j] = i;
	}
	return 0;
}
