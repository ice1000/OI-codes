#include <stdio.h>

int u[5005], n, m, p;

int find (int v) {
	return u[v] == v ? u[v] : (u[v] = find(u[v]));
}

void merge (int a, int b) {
	int t1 = find(a), t2 = find(b);
	if (t1 ^ t2) u[t1] = t2;
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
