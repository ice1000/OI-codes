#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n,m,tot=1,k=1;
int father[100+10];
int map[110][110];
int head[100+10];
int ans=0;

struct edge
{
    int u,v,w;
    friend bool operator < (edge a,edge b)
    {
        return a.w < b.w;
    }
}e[100*100+10];

struct newedge
{
    int v,w,next;
}ne[100+10];

void adde(int u,int v,int w)
{
     ne[k].v=v;
     ne[k].w=w;
     ne[k].next=head[u];
     head[u]=k++;
}

void chushi()
{
    for(int i=1;i<=n;i++)father[i]=i;
}

int find(int x)
{
    if((father[x]==x))return x;
    else return father[x]=find(father[x]);
}

void unio(int x,int y,int z)
{
    int fx=find(x);
    int fy=find(y);
    if(fx!=fy)
    {
        adde(x,y,z);
        father[fx]=fy;
        ans+=z;
    }
}

void readdata()
{
    freopen("p.in","r",stdin);
    freopen("k.out","w",stdout);
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    {
        scanf("%d",&map[i][j]);
        e[tot].u=i;
        e[tot].v=j;
        e[tot].w=map[i][j];
        tot++;
    }
}

void kruskal()
{
    sort(e+1,e+tot);
    chushi();
    for(int i=1;i<=tot-1;i++)
    {
        int u=e[i].u,v=e[i].v,w=e[i].w;
        unio(u,v,w);
    }
    printf("%d\n",ans);
}

void printG()
{
     for(int i=1;i<=n;i++)
     {
         for(int j=head[i];j!=-1;j=ne[j].next)
         {
             int v=ne[j].v,w=ne[j].w;
             printf("%d->%d %d\n",i,v,w);
         }
     }
}


int main()
{
    readdata();
    kruskal();
    printG();
    return 0;
}
