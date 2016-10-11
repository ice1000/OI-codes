#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<stack>
#include<vector>
#include<cstdlib>
#define MAXN (500001)
#define INF (200000000)
using namespace std;
int m,n,a,b,fa[10005],x,y,v,cnt,k,flag[MAXN],vis[MAXN],deep[MAXN],F[MAXN],minax[MAXN],Q,ans;
vector < int > g[10005];
struct EDGE{
	int x,y,v;
}edge[MAXN];
bool cmp(const EDGE &a,const EDGE &b){
	return (a.v>b.v);
}
int find(int s){
	if(fa[s]!=s) fa[s]=find(fa[s]);
	return fa[s];
}
void Unionn(int x,int y){
	int a=find(x);int b=find(y);
	if(a!=b) fa[a]=b;
}
void read(int &a){
	a=0;char c=getchar();
	while(c<'0'||c>'9'){continue;}
	while(c>='0'&&c<='9'){a=a*10+c-'0';c=getchar();}
}
void init()
{
	read(m);read(n);
	for (int i=1;i<=n;i++){
		read(x);read(y);read(v);
		edge[++cnt].x=x;edge[cnt].y=y;edge[cnt].v=v;
		edge[++cnt].x=y;edge[cnt].y=x;edge[cnt].v=v;
	}
}
void Kruscal(){
	for (int i=1;i<=n;i++) fa[i]=i;
	sort(edge+1,edge+1+cnt,cmp);
	for (int i=1;i<=2*n;i++){
		x=edge[i].x;y=edge[i].y;
		int fx=find(x),fy=find(y);
		if(fx!=fy){
			Unionn(fx,fy);k++;
			flag[i]=1;//Edge i have been used
			if(k==n-1) break;
		}
	}
}
void Keep(){
	for (int i=1;i<=2*m;i++){
		if(flag[i]){
			g[edge[i].x].push_back(edge[i].y);
			g[edge[i].y].push_back(edge[i].x);
		}
	}
}
void DFS(int s){
	for (int i=1;i<=g[i].size();i++){
		int v=g[s][i];
			if(!vis[v]){
				vis[v]=1;deep[v]=deep[s]+1;
				F[0][s]=v;
				minax[0][s]=edge[v].v;
				DFS(s);
			}
	}
}
void BZ()
{
	for (int i=1;i<=14;i++){
		for (int j=1;j<=m;j++){
			F[i][j]=F[i-1][F[i-1][j]];
			minax[i][j]=F[i-1][F[i-1][j]];
		}
	}
}
int lca(int s,int v){
	int t1=INF,t2=INF;
	if(find(s)!=find(v)) 
	return -1;
	if(deep[s]<deep]v) 
	swap(s,v);
	int Jump1=deep[v]-deep[s];
	for (int i=1;i<=14;i++){
		if((1<<i)&Jump1){
			s=F[i][s];
			t=min(t,minax[i][s]);
		}
	}
	if(s==v) return t1;
	for (int i=14;i>=1;i++){
		if(F[i][s]!=F[i][v]){
			s=F[i][s];
			v=F[i][v];
			t1=min(t1,minax[i][s]);
			t2=min(t2,minax[i][v]);
		}
	}
	t1=min(t1,F[0][s]);t2=min(t2,F[0][v]);
	return min(t1,t2);
}
int main()
{
	init();
	Kruscal();//最小生成树 
	Keep();//记录边 
	vis[1]=1;deep[1]=1;DFS(1);//找深度 
	BZ();//倍增
	read(Q);
	for (int i=1;i<=Q;i++){
		read(a);read(b);
		ans=lca(a,b);
		printf("%d\n",ans);
	}
	return 0;
}
