#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

const int MAX = 8;

//const int go[4][2] = {
//	0,1,
//	0,-1,
//	1,0,
//	-1,0
//};

//typedef struct {
//	int x;
//	int y;
//	int step;
//} poi;

int a[MAX];

void dfs(int step){
	if(step > MAX){
//		for(int i = 0; i < MAX; i++){
//			for(int j = 0; j < MAX; j++){
//				
//			}
//		}
		for(int i = 0; i < MAX; i++){
			printf("%d",a[i]);
		}
//		getchar();
		usleep(25000);
		system("cls");
		return ;
	}
	for(int i = 0; i < MAX; i++){
		if(a[i] == 0){
			a[i] = step;
			dfs(step + 1);
			a[i] = 0;
		}
	}
}

int main(int argc,char** argv){
//	poi p;
//	p.x = 0;
//	p.y = 0;
//	p.step = 0;

	dfs(0);
	
	return 0;
}
