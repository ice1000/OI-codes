#include<stdio.h>
#include<string.h>
#define INF 0xfffffff
const int MAXV = 1000, MAXE = 200000;
struct edge {int next, to, cap;} e[MAXE];
int head[MAXV], tot, V;
void gInit() {memset(head, -1, sizeof(head)); tot = 0; V = 0;}
void add_edge(int u, int v, int cap)
{
    e[tot] = (edge) {head[u], v, cap}; head[u] = tot++;
    e[tot] = (edge) {head[v], u, 0}; head[v] = tot++;
}

int h[MAXV];//距离标号数组
int numh[MAXV];//用于GAP优化的统计高度数量数�?
int iter[MAXV];//当前弧优�?
int Prev[MAXV];//前驱结点
int sap(int s, int t)
{
    memset(h, 0, sizeof(h));
    memset(numh, 0, sizeof(numh));
    memset(Prev, -1, sizeof(Prev));
    for(int i = 0; i < V; ++i) iter[i] = head[i];//�?开始的图，初始化为第一条邻接边
    numh[0] = V;
    int u = s, max_flow = 0, i;
    while(h[s] < V)
    {
        if(u == t)//增广成功
        {
            int flow = INF, neck = -1;
            for(u = s; u != t; u = e[iter[u]].to)
            {
                if(flow > e[iter[u]].cap)
                {
                    neck = u;
                    flow = e[iter[u]].cap;
                }
            }//寻找"瓶颈"�?
            for(u = s; u != t; u = e[iter[u]].to)
            {
                e[iter[u]].cap -= flow;
                e[iter[u] ^ 1].cap += flow;
            }//修改路径上的边容�?
            max_flow += flow;
            u = neck;//下次增广从瓶颈边之前的结点开�?
        }
        //寻找可行�?
        for(i = iter[u]; ~i; i = e[i].next)
            if(e[i].cap > 0 && h[u] == h[e[i].to] + 1)
                break;
        if(i != -1)
        {
            iter[u] = i;
            Prev[e[i].to] = u;
            u = e[i].to;
        }
        else
        {
            if(0 == --numh[h[u]]) break;//GAP优化
            iter[u] = head[u];
            for(h[u] = V, i = head[u]; ~i; i = e[i].next)
                if(e[i].cap > 0 && h[e[i].to] < h[u])
                    h[u] = h[e[i].to];
            ++h[u];
            ++numh[h[u]];
            if(u != s) u = Prev[u];//从标号并且从当前结点的前驱重新增�?
        }
    }
    return max_flow;
}
int main(){
	int f,d,n;
	while(~scanf("%d%d%d",&n,&f,&d)){
		gInit();
		V=2+f+d+n+n;
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
		printf("%d\n",sap(0,1));
	}
	return 0;
}
