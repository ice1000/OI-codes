#include <stdio.h>
#include <set>

int main(int argc, const char *argv[]) {
	std::set<long long> pt = *new std::set<long long>;
	long long n, ans = 1;
	scanf("%lli", &n);
	while (n --> 0) {
		long long p, r;
		scanf("%lli %lli", &p, &r);
		if (pt.count(p - r) && pt.count(p + r)) ans += 2;
		else ans++;
		pt.insert(p - r), pt.insert(p + r);
	}
	printf("%lli", ans);
}
