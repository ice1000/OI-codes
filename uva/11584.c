#include <stdio.h>
#include <string.h>
char a[1005];
int l;
int damn(int left,int right){
	while(left<right)
		if(a[left++]!=a[right--])
			return 0;
	return 1;
}
int min(int a, int b) {
	return a > b ? b : a;
}
int dp[1005];
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%s",a+1);
		l=strlen(a+1);
		dp[0]=0;
		int i,j;
		for(i=1;i<=l;++i)
			dp[i]=0xFFFFF;
		for(i=1;i<=l;++i)
			for(j=1;j<=i;++j)
				if(damn(j,i))
					dp[i]=min(dp[i],dp[j-1]+1);
		printf("%d\n", dp[l]);
	}
	return 0;
}