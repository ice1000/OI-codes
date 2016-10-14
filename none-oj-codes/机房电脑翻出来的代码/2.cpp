#include<cstdio>
#include<cstring>
using namespace std;
long long n,d,k;
long long mod=1000000007;
long long a[1010],b[1010];

void jzcf(long long a[],long long b[])
{
	long long c[1010]={0};
	memset(c,0,sizeof(c));
	for(int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			int temp=j-i;
			if (temp<0) temp+=n;                                                       ;
			c[i]+=a[j]*b[temp]%mod;
		}
	}
	for(int i=0;i<n;i++) a[i]=c[i]%mod;
}
	
int main()
{
	scanf("%lld%lld%lld",&n,&d,&k);

	for(int i=0;i<n;i++) scanf("%lld",a+i);
	b[0]=1;
	for(int i=1;i<=d;i++) b[i]=b[n-i]=1;
	while (k)
	{
		if (k%2==1) jzcf(a,b);	
		jzcf(b,b);
		k=k>>1;
	}
	printf("%lld",a[0]);
	for(int i=1;i<n;i++) printf(" %lld",a[i]);
}
		
	
