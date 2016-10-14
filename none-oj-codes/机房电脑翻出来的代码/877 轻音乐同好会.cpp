#include <cstdio>
#include <algorithm>

int n;
struct Stone{
	int h,pos;
}st[1010];
bool cmp(Stone a, Stone b){
	return a.h < b.h;
}

int p[1010],maxp;	//离散化后的高度
int dp[1010][1010];	//dp[Hi][Hj] = 第一个人跳到高度Hi,第二个人跳到高度Hj时跳过石头的最大个数
int tr[1010][1010];	//tr <- c[i][j] = max{ dp[maxp-i .. maxp][maxp-j .. maxp] }

inline int max(int a,int b){
	return (a>b) ? a : b;
}

void update(int pos1,int pos2,int val){
	for( int i=pos1; i<=maxp; i+=i&-i )
		for( int j=pos2; j<=maxp; j+=j&-j )
			tr[i][j] = max(tr[i][j],val);
}
int query(int pos1,int pos2){
	int ans=0;
	for( int i=pos1; i; i-=i&-i )
		for( int j=pos2; j; j-=j&-j )
			ans = max(ans,tr[i][j]);
	return ans;
}

void reset(){
	for(int i=0;i<=maxp;i++)
		for(int j=0;j<=maxp;j++)
			dp[i][j]=tr[i][j]=0;
}
int DP() {
	reset();
	for(int i=0;i<n;i++){	//枚举石头
		for(int h=0;h<maxp;h++){	//不跳的人的当前高度
			dp[p[i]][h] = max(dp[p[i]][h], query(maxp-p[i], maxp-h)+1 );	//第一个人跳
			dp[h][p[i]] = max(dp[h][p[i]], query(maxp-h, maxp-p[i])+1 );	//第二个人跳
			update(maxp-p[i], maxp-h, dp[p[i]][h]);
			update(maxp-h, maxp-p[i], dp[h][p[i]]);
		}
	}
	return query(maxp-1,maxp-1);
}

int main() {
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&st[i].h);
		st[i].pos = i;
	}
	std::sort(st,st+n,cmp);
	maxp = p[st[0].pos] = 0;
	for(int i=1;i<n;i++)
		if(st[i].h > st[i-1].h) p[st[i].pos] = ++maxp;
		else p[st[i].pos] = maxp;
	maxp++;
	printf("%d\n",DP());
	return 0;
}
