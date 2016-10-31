#include <stdio.h>

int u[5005], n, m, p, depth[5005];

int find (int v) {
	return u[v] == v ? u[v] : (u[v] = find(u[v]));
}

void merge (int a, int b) {
  int x = find(a), y = find(b);
	if (x ^ y) {
	  if (depth[x] == depth[y]) {
	    u[x] = y;
	    ++depth[y];
    } else if (depth[x] > depth[y]) {
      u[y] = x;
    } else {
	    u[x] = y;
    }
  }
}

int main (int argc, char *argv[]) {
	int i, j, k;
	scanf("%i %i %i", &n, &m, &p);
	for (i = 0; i < n; ++i) u[i] = i;
	for (i = 0; i < m; ++i) {
		scanf("%i %i", &j, &k);
		merge(j, k);
	}
	for (i = 0; i < p; ++i) {
		scanf("%i %i", &j, &k);
		printf(find(j) == find(k) ? "Yes\n" : "No\n");
	}
	return 0;
}



