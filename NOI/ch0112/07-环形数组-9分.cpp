#include<stdio.h>

int cnt = 0;
int dir[110];

void search(int word, int M){
	for(unsigned i = 0; i < M; i++)
		if(dir[i] == word) return;
	// not found , extend the size of the dic
	dir[++cnt%M] = word;
}

int main(int argc,char* argv[]){
	int M = 0;
	int N = 0;
	scanf("%d%d",&M,&N);
	int a;
	for(int i = 0; i < N; i++){
		scanf("%d",&a);
		search(a, M);
	}
	printf("%d",cnt);
	return 0;
}
