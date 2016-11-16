#include <stdio.h>
#include <string.h>

struct Node {
	int x, y;
} nodes[210];

typedef struct Node Node;

void setValue(Node *node, int x, int y) {
	node->x = x;
	node->y = y;
}

int n, k, ret, node_idx;
char map[20][20], mark[20][2];

void dfs(int idx, int selected) {
	if (selected == k) {
		++ret;
		return;
	}
	if (idx >= node_idx) return;
	if (!mark[nodes[idx].x][0] && !mark[nodes[idx].y][1]) {
		++mark[nodes[idx].x][0];
		++mark[nodes[idx].y][1];
		dfs(idx + 1, selected + 1);
		--mark[nodes[idx].x][0];
		--mark[nodes[idx].y][1];
	}
	dfs(idx + 1, selected);
}

int main(int argc, const char *argv[]) {
	freopen("chess.in", "r", stdin);
	freopen("chess.out", "w", stdout);
	int i, j;
	scanf("%i %i", &n, &k);
	memset(map, '.', sizeof(map));
	for (i = 0; i < n; ++i) {
		scanf("%s", map[i]);
		for (j = 0; j < n; ++j) {
			if (map[i][j] == '#') setValue(&nodes[node_idx++], i, j);
		}
	}
	dfs(0, 0);
	printf("%i", ret);
}

/*
2 1
#.
.#

4 4
...#
..#.
.#..
#...
*/
