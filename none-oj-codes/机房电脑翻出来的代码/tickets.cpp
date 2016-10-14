#include <cstdio>

int N;
struct Node{
	int val,num,s1,s2;
}tr[200050],cnt=1;
const int rt=1;

void reset(){
	tr[0].num=0;
	tr[1]
}
inline int newNode(int val){
	tr[++cnt]=(Node){val,1,0,0};
	return cnt;
}

void insert(int pos,int val){
	int x=rt;
	while(true){	//搜到底 
		tr[x].num++;
		if(tr[tr[x].s1].num>=pos){	//插入到左儿子
			if(!tr[x].s1) {
				tr[x].s1=newNode(val);
				return;
			}
			x=tr[x].s1;
		}
		else if(tr[tr[x].s1].num+1==pos) {	//插入到中间
			tr[++cnt]=(Node){val,tr[x].num+1,tr[x].s1,x};
			tr[x].num=tr[tr[x].s2].num+1;
			tr[x].s1=0;
			return;
		}
		else{	//插入到右儿子
			if(!tr[x].s2) {
				tr[x].s2=newNode(val);
				return;
			}
			pos-=tr[tr[x].s1].num+1;
			x=tr[x].s2;
		}
	}
}

int main() {
	freopen("tickets.in","r",stdin);
	freopen("tickets.out","w",stdout);
	while(scanf("%d",&N)){
		reset();
		
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
