//多校联测 3
//Problem 342 道路
//Time Limit: 1000 MS
//Memory Limit : 128000 KB
//Enrong
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 0x3f3f3f3f
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

struct node
{
	int lef,rig,abo,bel,Ma,Mi;
}mar[110][110];
int k,m,n,o,i,p,s,t,head,tail,flag,tx,ty,ma[110][110],book[110][110],nex[4][2]={{0,-1},{-1,0},{0,1},{1,0}};
void dfs(int x,int y)
{
	if (x==n-1 && y==n-1 && mar[n-1][n-1].abo==1 && mar[n-1][n-1].lef==1)	return;
	for (k=0;k<4;k++)
	{
		tx=x+nex[k][0],ty=y+nex[k][1];
		if (tx<0||ty<0||tx>=n||ty>=n)	continue;
		if ((k==0&&mar[tx][ty].rig==1)||(k==1&&mar[tx][ty].bel==1)||(k==2&&mar[tx][ty].lef==1)||(k==3&&mar[tx][ty].abo==1))	continue;
		t=mar[tx][ty].Ma;
		mar[tx][ty].Ma=max(ma[tx][ty],mar[x][y].Ma),mar[tx][ty].Mi=min(ma[tx][ty],mar[x][y].Mi);
		book[tx][ty]=min(book[tx][ty],abs(mar[tx][ty].Ma-mar[tx][ty].Mi));
		mar[tx][ty].Ma=t;
		if (k==0)	mar[tx][ty].rig=1;
		if (k==1)	mar[tx][ty].bel=1;
		if (k==2)	mar[tx][ty].lef=1;
		if (k==3)	mar[tx][ty].abo=1;
		if (mar[tx][ty].rig==1 && mar[tx][ty].bel==1 && mar[tx][ty].lef==1 && mar[tx][ty].abo==1)	continue;
		dfs(tx,ty);
	}
}
int main()
{
	memset (book,INF,sizeof(book));
	scanf ("%d",&n);
	for (i=0;i<n;i++)	for (o=0;o<n;o++)	{scanf ("%d",&ma[i][o]);mar[i][o].Ma=ma[i][o],mar[i][o].Mi=ma[i][o];}
	for (i=0;i<n;i++)	mar[0][i].abo=1,mar[n-1][i].bel=1,mar[i][0].lef=1,mar[i][n-1].rig=1;
	dfs (0,0);
	printf ("%d\n",book[n-1][n-1]);
	return 0;
}
//Tried to DFS but failed on the update of the data..
