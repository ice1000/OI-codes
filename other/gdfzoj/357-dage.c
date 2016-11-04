//六校联测 4
//Problem 357 求方案
//Time Limit : 1000 MS
//Memory Limit : 128000 KB
//Enrong
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1234567

inline int in() {
	char ch=getchar();
	int x=0;
	while (ch<'0'||ch>'9')	ch=getchar();
	while (ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x;
}
int n,o,i,cmp,p,a[100005],k,temp,ans;
int main() {
	n=in(),temp=in();
	for (i=1; i<=n; i++)	a[i]=in();
	for (i=1; i<=n; i++) {
		cmp=a[i];
		if (cmp%temp==0)
			ans=(ans+1)%MOD;
		for (o=i+1; o<=n; o++) {
			cmp+=a[o];
			if (cmp%temp==0)
				ans=(ans+1)%MOD;
		}
	}
	printf ("%d\n",ans);
	return 0;
}
