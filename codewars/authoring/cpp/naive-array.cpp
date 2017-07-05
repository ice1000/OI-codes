#include <map>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef long long LL;
typedef unsigned long long uLL;
typedef map<int, int>::iterator mit;
typedef set<int>::iterator sit;

const int N = 2e5 + 10, M = 1e6 + 10;

int n, a[N];
uLL t[M], seed;

uLL rd() {
	return seed = seed * seed * 233252uLL + 323241uLL * seed + 324251314uLL;
}

const int B = 400, mod = 524288;

struct node {
	int x;
	uLL h;
	int w, pre;
} e[N];

int u[mod], st[N], top = 0, el = 0;

inline int nn() { return el < N - 1 ? (++el) : st[top--]; }

uLL tag[N], h[N], cnt[N];
int nxt[M], tot = 0;

inline int Hash(int x, uLL h) {
	return (x ^ (x << 7) ^ (x << 10) ^ (h >> 49) ^ (h >> 34) ^ (h >> 19) ^ (h >> 4) ^ h) & (mod - 1);
}
inline void inc(int x, uLL h, int d) {
	int ind = Hash(x, h);
	int *t = &u[ind];
	for(int i = u[ind]; i; i = e[i].pre) if (e[i].x == x && e[i].h == h) {
			e[i].w += d;
			if (!e[i].w) {
				(*t) = e[i].pre;
				st[++top] = i;
			}
			return;
		} else t = &e[i].pre;
	int t1 = nn();
	e[t1] = (node) { x, h, d, u[ind] };
	u[ind] = t1;
}

int qry(int x, uLL h) {
	int ind = Hash(x, h);
	for(int i = u[ind]; i; i = e[i].pre)
		if (e[i].x == x && e[i].h == h) return e[i].w;
	return 0;
}

void modi(int x, uLL d) {
	int tx = (x - 1) / B + 1;
	int ed = min(n, tx * B);
	tot -= cnt[tx];
	for(auto i = x; i <= ed; ++i) {
		inc(tx, h[i], -1);
		h[i] ^= d;
		inc(tx, h[i], 1);
	}
	tot += (cnt[tx] = qry(tx, tag[tx]));
	ed = (n - 1) / B + 1;
	for(auto i = tx + 1; i <= ed; ++i) {
		tot -= cnt[i];
		tag[i] ^= d;
		tot += (cnt[i] = qry(i, tag[i]));
	}
}

void init() {
	seed = 8473920485628474uLL;
	el = 0;
	memset(u, 0, sizeof(u));
	top = 0;
	memset(tag, 0, sizeof(tag));
	memset(h, 0, sizeof(h));
	memset(cnt, 0, sizeof(cnt));
	tot = 0;
	memset(nxt, 0, sizeof(nxt));
}

LL solve(int n0, int a0[]) {
	n = n0;
	for (auto i = 0; i < n; ++i)
		a[i + 1] = a0[i];
	init();
	for(int i = 1; i <= n; i++)
		if (!t[a[i]]) t[a[i]] = rd();
	LL ans = 0;
	tot = n;
	for(int i = 1; i <= n; i++)
		inc((i - 1) / B + 1, 0, 1), cnt[(i - 1) / B + 1]++;
	for(int i = n; i >= 1; i--) {
		int x = nxt[a[i]];
		if (x) modi(x, t[a[i]]);
		nxt[a[i]] = i;
		ans += tot - (i - 1);
	}
	return ans;
}

