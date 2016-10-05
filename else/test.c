// 2016-10-1 ice1000

#include <stdio.h>
#define lowbit(x) ((x) & (-(x)))

struct Node { int l, r, ls, rs, c; } tree[1001];
int a[1001], n;

// binary-indexed array
void add(int i, int v) { if (i <= n) a[i] += v, add(i + lowbit(i), v); }
int sum(int i) { return i ? a[i] + sum(i - lowbit(i)) : 0; }

// union set
int find(int n) { return n == a[n] ? n : find(a[n]); }
inline void merge(int x, int y) { if ((x = find(x)) ^ (y = find(y))) a[x] = y; }
/**
 int main(int argc, char *argv[]) {
	int i, j, k;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) scanf("%i", &j), add(i, j);

	return 0;
}
*/

// monotonous queue
int queue[999], begin = 0, end = 0;
int empty() { return queue[end] > begin; }
inline void push(int num) {
	// binary search can optimize
	while (empty() and queue[end] > num) --end;
	queue[++end] = num;
}
inline int pop(int num) {
	// binary search can optimize
	while (empty() and queue[begin] < num) ++begin;
	queue[--begin] = num;
}
inline int first() { return queue[begin]; }

// refix sum
int a[999], refix[999], idx[999], n, m, i, j;
refix[0] = a[0];
for (i = 1; i < n; ++i) refix[i] = refix[i - 1] + a[i];
for (i = 1; i < n; ++i) 

// kosarajo
// tarjan
// kruskal
