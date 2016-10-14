#include <cstdio>
#include <cstdlib>

int n;
struct Stone{
	int h,pos;
}st[1010];
int cmp(const void *a, const void *b){
	return *(int*)a - *(int*)b;
}
int p[1010],maxp;	//离散化后的高度
int dp[1010][1010];	//dp[Hi][Hj] = 第一个人跳到高度Hi,第二个人跳到高度Hj时跳过石头的最大个数

inline int max(int a,int b){
	return (a>b) ? a : b;
}

int query(int pos1,int pos2){
	int ans=0;
	for(int i=1;i<=pos1;i++)
		for(int j=1;j<=pos2;j++)
			ans=max(ans,dp[i][j]);
	return ans;
}

void reset(){
	for(int i=0;i<=maxp;i++)
		for(int j=0;j<=maxp;j++)
			dp[i][j]=0;
}
int DP() {
	reset();
	dp[p[0]][maxp-1] = dp[maxp-1][p[0]] = 1;
	for(int i=1;i<n;i++){	//枚举石头
		for(int h=0;h<maxp;h++){	//不跳的人的当前高度
			dp[p[i]][h] = max( dp[p[i]][h], query(maxp-p[i], maxp-h)+1 );	//第一个人跳
			dp[h][p[i]] = max( dp[h][p[i]], query(maxp-h, maxp-p[i])+1 );	//第二个人跳
		}
	}
	return query(maxp,maxp);
}

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&st[i].h);
		st[i].pos = i;
	}
	qsort(st,sizeof(Stone),n,cmp);
	maxp = p[st[0].pos] = 0;
	for(int i=1;i<n;i++)
		if(st[i].h > st[i-1].h) p[i] = ++maxp;
		else p[i] = maxp;
	maxp++;
	printf("%d",DP());
	return 0;
}
