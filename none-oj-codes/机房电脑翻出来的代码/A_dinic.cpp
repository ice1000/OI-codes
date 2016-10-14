#include<stdio.h>
#include<string.h>
#include<vector>
#include<queue>
#define INF 0xfffffff
using namespace std;
const int MAXV = 1000, MAXE = 200000;
struct edge {int to, cap, rev;};
vector <edge> G[MAXV];
int level[MAXV];
int iter[MAXV];
void gInit()
{
    for(int i = 0; i < MAXV; i++)
        G[i].clear();
}
void add_edge(int from, int to, int cap)
{
    G[from].push_back((edge) {to, cap, (int) G[to].size()});
    G[to].push_back((edge) {from, 0, (int) G[from].size() - 1 });
}
bool bfs(int s, int t)
{
    memset(level, -1, sizeof(level));
    queue <int> que;
    level[s] = 0;
    que.push(s);
    while(!que.empty())
    {
        int v = que.front();
        que.pop();
        for(int i = 0; i < (int)G[v].size(); i++)
        {
            edge& e = G[v][i];
            if(e.cap > 0 && level[e.to] < 0)
            {
                level[e.to] = level[v] + 1;
                que.push(e.to);
            }
        }
    }
    return level[t] != -1;
}

int dfs(int v, int t, int f)
{
    if(v == t) return f;
    for(int& i = iter[v]; i < (int)G[v].size(); i++)
    {
        edge& e = G[v][i];
        if(e.cap > 0 && level[v] < level[e.to])
        {
            int d = dfs(e.to, t, min(f, e.cap));
            if(d > 0)
            {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t)
{
    int flow = 0, cur_flow;
    while(bfs(s, t))
    {
        memset(iter, 0, sizeof(iter));
        while((cur_flow = dfs(s, t, INF)) > 0) flow += cur_flow;
    }
    return flow;
}
int main(){
	int f,d,n;
	while(~scanf("%d%d%d",&n,&f,&d)){
		gInit();
		int t;
		for(int i=0;i<f;i++){
			scanf("%d",&t);
			add_edge(0,2+i,t);
		}
		for(int i=0;i<d;i++){
			scanf("%d",&t);
			add_edge(2+f+i,1,t);
		}
		char ch[210];
		for(int j=0;j<n;j++){
			scanf("%s",ch);
			for(int i=0;i<f;i++){
				if(ch[i]=='Y')
					add_edge(2+i,2+f+d+j,1);
			}
		}
		for(int j=0;j<n;j++){
			scanf("%s",ch);
			for(int i=0;i<d;i++){
				if(ch[i]=='Y')
					add_edge(2+f+d+n+j,2+f+i,1);
			}
		}
		for(int j=0;j<n;j++)
			add_edge(2+f+d+j,2+f+d+n+j,1);
		printf("%d\n",max_flow(0,1));
	}
	return 0;
}
