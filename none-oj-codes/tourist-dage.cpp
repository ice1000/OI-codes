//NOIP 2016 UKHH GMIJ CQWY QIIZ PFJM DAY 2
//YTEY TFHZ FTJF UKDZ JGHM tourist.cpp/c/pas
//Time Limit : 1000 MS
//Memory Limit : 128 M
//LDNU IPWK - Enrong
#include <stdio.h>
#include <list>
#include <map>
#include <algorithm>

using namespace std;
#define int long long

int in()
{
	int ch = getchar(), x = 0, f = 1;
	while (ch < '0' || ch > '9')
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}

int a[100010], n, ansz, ansm, mi, mu, zi;
#undef int
int main() {
#define int long long
	freopen("tourist.in", "r", stdin);
	freopen("tourist.out", "w", stdout);
	n = in();
	for (int i = 1; i <= n; ++i)
		a[i] = in();
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; ++i)
	{
		ansz += a[i];
		for (int j = i + 1; j <= n; ++j)
		{
			mi = a[j] - a[i];
			ansz += mi * 2;
		}
	}
	ansm = n;
	mu = ansm;
	zi = ansz;
	int gcd = __gcd(mu, zi);
	ansm = ansm / gcd;
	ansz = ansz / gcd;
	printf("%lld %lld\n", ansz, ansm);
	return 0;
#undef int
}


