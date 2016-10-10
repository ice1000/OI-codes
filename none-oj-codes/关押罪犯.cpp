#include <stdio.h>
#include <string.h>
#define true 1
#define false 0

const int MAXN = 20000 + 10,MAXM = 200000 + 10;

struct egde {
  int v,next;
}e[MAXM];

int n,m,ans,cnt = 1,mx = -1;
int a[MAXM],b[MAXM],c[MAXM];
int head[MAXN],col[MAXN];
int flag;

void adde(int u,int v) {
  e[cnt].v = v;
  e[cnt].next = head[u];
  head[u] = cnt++;
}

void build(int mid) {
  int i;
  memset(head, -1, sizeof(head));
  for(i = 1; i <= m; i++)
    if(c[i] > mid) {
      adde(a[i],b[i]);
      adde(b[i],a[i]);
    }
}

void dfs(int u) {
  if(!flag) return;
  int i;
  for(i = head[u]; i != -1; i = e[i].next) {
    int v = e[i].v;
    if(col[v] == -1) {
      col[v] = col[u] ^ 1;
      dfs(v);
    }
    else if(col[u] == col[v]) {
      flag = 0;
      return;
    }
  }
}

void work() {
  int l = 0, r = mx, mid, i;
  while(l <= r) {
    mid = (l + r) >> 1;
    build(mid);
    memset(col, -1, sizeof(col));
    flag = 1;
    for(i = 1; i <= n; i++) {
      if(col[i] == -1) {
	col[i] = 0;
	dfs(i);
      }
      if(!flag) break;
    }
    if(flag) {
      ans = mid;
      r = mid - 1;
    }
    else l = mid + 1;
  }
}

int main() {
  int i;
  scanf("%d %d", &n, &m);
  for(i = 1; i <= m; i++) {
    scanf("%d %d %d", &a[i], &b[i], &c[i]);
    if (c[i] > mx) mx = c[i];
  }
  work();
  printf("%d\n", ans);
  return 0;
}
