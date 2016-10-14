#include <cstdio>

int N;
struct Node{
	int l,r,sum,lazy;
}tr[100000<<2];

inline void pushup(int x){
	tr[x].sum=tr[x<<1].sum+tr[x<<1|1].sum;
}
inline void pushdown(int x){
	if(!tr[x].lazy) return;
	tr[x<<1].sum=(tr[x<<1].r-tr[x<<1].l+1)*tr[x].lazy;
	tr[x<<1|1].sum=(tr[x<<1|1].r-tr[x<<1|1].l+1)*tr[x].lazy;
	tr[x<<1].lazy=tr[x<<1|1].lazy=tr[x].lazy;
	tr[x].lazy=0;
}
void build(int x,int l,int r){
	tr[x]=(Node){l,r,r-l+1};
	if(l<r){
		int mid=l+r>>1;
		build(x<<1,l,mid);
		build(x<<1|1,mid+1,r);
	}
}
int L,R,val;
void update(int x){
	if(L<=tr[x].l && tr[x].r<=R){
		tr[x].lazy=val;
		tr[x].sum=(tr[x].r-tr[x].l+1)*val;
		return;
	}
	pushdown(x);
	int mid=tr[x].l+tr[x].r>>1;
	if(L<=mid) update(x<<1);
	if(R>mid) update(x<<1|1);
	pushup(x);
}

int main() {
	freopen("hook.in","r",stdin);
	freopen("hook.out","w",stdout);
	int T,Q;
	scanf("%d",&T);
	for(int k=1;k<=T;k++){
		scanf("%d%d",&N,&Q);
		build(1,1,N);
		for(int i=0;i<Q;i++){
			scanf("%d%d%d",&L,&R,&val);
			update(1);
		}
		printf("Case %d: The total value of the hook is %d.\n",k,tr[1].sum);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
