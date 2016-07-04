#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
const int inf=0x3f3f3f3f;

int n,m,k=1,cnt;
int head[1001];
int heap[1001];
int dis[1001];
int pos[1001];

struct edge {
	int v,w,next;
} e[1000*1000+10];

void adde(int u,int v,int w) {
	e[k].v=v;
	e[k].w=w;
	e[k].next=head[u];
	head[u]=k++;
}

void readdata() {
	memset(head,-1,sizeof(head));
	memset(dis,inf,sizeof(dis));
	int a,b,c;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++) {
		scanf("%d%d%d",&a,&b,&c);
		adde(a,b,c);
		adde(b,a,c);
	}
}

void heapup(int x) {
	while(x>1) {
		if(dis[heap[x>>1]]>dis[heap[x]]) {
			swap(heap[x>>1],heap[x]);
			swap(pos[heap[x>>1]],pos[heap[x]]);
			x>>=1;
		} else break;
	}
}

void heapdown(int x) {
	int k;
	while((x<<1)<=cnt) {
		if((x<<1)==cnt||dis[heap[x<<1]]<dis[heap[(x<<1)+1]])
			k=x<<1;
		else k=(x<<1)+1;
		if(dis[heap[x]]>dis[heap[k]]) {
			swap(heap[x],heap[k]);
			swap(pos[heap[x]],pos[heap[k]]);
			x = k;
		} else break;
	}
}

int pop() {
	int ret = heap[1];
	swap(heap[1], heap[cnt]);
	swap(pos[heap[1]], pos[heap[cnt]]);
	cnt--;
	heapdown(1);
	return ret;
}

void push(int v, int w) {
	dis[v] = w;
	heap[++cnt] = v;
	pos[v] = cnt;
	heapup(cnt);
}

void prim() {
	int ans = 0;
	dis[1] = 0;
	push(1, 0);
	for(int i = 2; i <= n; i++)
		push(i, inf); // init heap
	for(int i = 1; i <= n; i++) {
		int u = pop(); // first (smallest)
		ans += dis[u];
		pos[u] = -1; // mark
		for(int i = head[u]; i != -1; i = e[i].next) {
			int v = e[i].v;
			if(pos[v] != -1 && dis[v] > e[i].w) {
				dis[v] = e[i].w;
				heapup(pos[v]);
				heapdown(pos[v]);
			}
		}
	}
	cout<<ans;
}

int main() {
	readdata();
	prim();
	return 0;
}
