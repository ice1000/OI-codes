#include <map>
#include <algorithm>
#include <set>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <iostream>

// #include <naive-array.cpp>

using namespace std;

namespace solution {
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
}

Describe(Tests) {
	It(should_work_for_exmaple) {
		int a[] = {2, 2, 2, 3};
		Assert::That(solve(4, a), Equals(7));
	}

	It(should_work_for_larger_tests) {
		int a[] = {2, 5, 2, 3, 6,  7, 8, 23, 23, 13,  65, 31, 3, 4, 3};
		Assert::That(solve(15, a), Equals(53));
		int a1[N] = {6,1,7,4,6,7,1,4,7,1,4,6,6,7,4,1,6,4,7,1,4,5,3,2,1,6,9};
		Assert::That(solve(27, a1), Equals(114));
	}

	It(shoud_work_for_random_tests_n_1000_An_1000) {
		srand((unsigned)time(NULL));
		int count = 5;
		cout << "<p><font color=\"green\">n == 1000, a[n] <= 1000</font></p>" << endl;
		while (count --> 0) {
			auto array = new int[1000]();
			for (auto i = 0; i < 1000; ++i) {
				array[i] = rand() % 1000;
			}
			Assert::That(solve(1000, array), Equals(solution::solve(1000, array)));
			delete array;
		}
	}

	It(shoud_work_for_random_tests_n_1000_An_10000) {
		srand((unsigned)time(NULL));
		cout << "<p><font color=\"blue\">n == 1000, a[n] <= 10000</font></p>" << endl;
		int count = 5;
		while (count --> 0) {
			auto array = new int[1000]();
			for (auto i = 0; i < 1000; ++i) {
				array[i] = rand() % 10000;
			}
			Assert::That(solve(1000, array), Equals(solution::solve(1000, array)));
			delete array;
		}
	}

	It(shoud_work_for_random_tests_n_20000_An_100000) {
		srand((unsigned)time(NULL));
		cout << "<p><font color=\"yellow\">n == 19999, a[n] <= 100000</font></p>" << endl;
		int count = 5;
		while (count --> 0) {
			auto array = new int[19999]();
			for (auto i = 0; i < 19999; ++i) {
				array[i] = rand() % 100000;
			}
			Assert::That(solve(19999, array), Equals(solution::solve(19999, array)));
			delete array;
		}
	}

	It(shoud_work_for_random_tests_n_100000_An_100000) {
		srand((unsigned)time(NULL));
		cout << "<p><font color=\"red\">n == 100000, a[n] <= 100000</font></p>" << endl;
		cout << "<p><font color=\"red\">test data will be stronger than you expect.</font></p>" << endl;
		cout << "<p><font color=\"red\">I've done that on purpose.</font></p>" << endl;
		int count = 5;
		auto r = new int[64]();
		for (auto i = 0; i < 64; ++i) {
			r[i] = rand() % 100000;
		}
		while (count --> 0) {
			auto array = new int[100000]();
			for (auto i = 0; i < 100000; ++i) {
				if (i < 80000) array[i] = r[rand() % 64];
				else array[i] = rand() % 100000;
			}
			Assert::That(solve(100000, array), Equals(solution::solve(100000, array)));
			delete array;
			delete r;
		}
	}
};
