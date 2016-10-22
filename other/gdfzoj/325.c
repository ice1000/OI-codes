#include <stdio.h>
#include <string.h>

#define size 200005

/// front star
int head[size], next[size], mark[size], from[size], to[size], n;
int ans = 0;

void dfs(int root) {
//	printf("dfs root = %i\n", root);
	int i, j, ended = 0, started = 0;
	for (i = head[root]; ~i; i = next[i]) {
		++mark[to[i]];
		dfs(to[i]);
		--mark[to[i]];
	}
	for (j = 1; j <= n; ++j) {
		if (mark[j]) {
			++started;
		}
		if (started && !mark[j]) {
			++ended;
		}
		if (ended && mark[j]) {
			break;
		}
	}
	if (j > n) {
		++ans;
	}
}

int main(int argc, char *argv[]) {
	int i, j, k, root = 1;
	memset(head, -1, sizeof(head));
	memset(next, -1, sizeof(next));
	memset(from, -1, sizeof(from));
	memset(to, -1, sizeof(to));
	scanf("%i", &n);
	for (i = 1; i < n; ++i) {
		scanf("%i %i", &j, &k);
		to[i] = k;
		next[i] = head[j];
		head[j] = i;
		from[k] = j;
		while (~from[root]) {
			root = from[root];
		}
	}
//	printf("root = %i\n", root);
	dfs(root);
	printf("%i", ans);
	return 0;
}

/*
5
2 3
2 1
2 4
5 2
*/
