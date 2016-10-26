#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
	int k,sum=0,i=1,n=1,flag=0;
	scanf("%d",&k);
	while(i<=k)
	{
		sum+=n;
		flag++;
		if(flag==n)
		{
			flag=0;
			n++;
		}
		i++;
	}
	printf("%d",sum);
	return 0;
}

