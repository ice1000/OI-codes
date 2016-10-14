#include<cstdio>
using namespace std;

long long mod=1000000007;

int main()
{
	long long n,ans=1;
	int temp=2;
	scanf("%lld",&n);
	while (n)
	{
		if(n%2==1) ans*=temp;
		ans%=mod;
		temp*=temp;
		temp=temp%mod;
		n>>=1;
	}
	printf("%lld",ans);
}
