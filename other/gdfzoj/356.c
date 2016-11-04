#include <stdio.h>

#define lowbit(x) ((x) & (-(x)))
#define int long long
#define size 2000010 << 1

int bit[size], n, mem[size];

inline void add(int end, int value) {
	if (end < n) bit[end] += value, add(end + lowbit(end), value);
}

inline int sum(int end) {
	if (mem[end]) return mem[end];
	return (mem[end] = (end ? bit[end] + sum(end - lowbit(end)) : 0));
}

inline int in() {
	int f = 1,p = 0; char c = getchar();
	while (c > '9' || c < '0') { if(c == '-' ) f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { p = p * 10 + c - '0'; c = getchar(); }
	return f * p;
}

#undef int
int main(int argc, const char *argv[]) {
#define int long long
	int i, j, k, l, x, y;
	n = in();
	for (i = 0; i < n; ++i) {
		j = in(), k = in();
		add(j, 1);
		add(k + 1, -1);
	}
	l = 0;
	for (i = 1; i <= n; ++i) {
		x = sum(i);
		if (x > l) {
			l = x;
		}
	}
	printf("%lli", x);
	return 0;
}

/*
5
1 10
2 4
3 6
5 8
4 7
*/

