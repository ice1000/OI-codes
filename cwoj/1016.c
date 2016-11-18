#include <stdio.h>
#include <string.h>

#define ms(x, y) memset((x), (y), sizeof(x))
#define INF 0x7f7f7f7f
#define size 5001
#define true 1
#define false 0

int head[size], next[size], value[size], target[size];
int dis[size], visit[size], inq[size];
int queue[size], begin = 0, end = 0;
int m, n;

inline int spfa(int s) {
	int i, j;
	for (i = 0; i <= n; ++i) dis[i] = INF;
	queue[end++] = s;
	begin = 0;
	++inq[s];
	dis[s] = 0;
	while (begin < end) {
		i = queue[begin++ % size];
//		printf("%i\n", head[i]);
		for (j = head[i]; ~j; j = next[j]) {
//		  printf("%i\n", value[j]);
			if (dis[target[j]] > dis[i] + value[j]) {
				dis[target[j]] = dis[i] + value[j];
				if (!inq[target[j]]) {
					++inq[target[j]];
					queue[end++ % size] = target[j];
					if (++visit[i] >= n) return true;
				}
			}
		}
		inq[i] = 0;
	}
	return false;
}

int main(int argc, const char *argv[]) {
	int i, j;
	scanf("%i %i", &n, &m);
	ms(head, -1), ms(next, -1), ms(inq, 0), ms(visit, 0);
	for (i = 0; i < m; ++i) {
		scanf("%i %i %i", &j, &target[i], &value[i]);
		next[i] = head[j];
		head[j] = i;
	}
	if (spfa(1) || dis[n] < 0) printf("Trapped in loop!");
	else printf("%i", dis[n]);
	return 0;
}

/*
3 3
1 2 -1
2 3 -1
3 1 -1
*/

