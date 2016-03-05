#include<stdio.h>
#include<queue>

using namespace std;

const int MAX = 3;

const int go[4][2] = {
	0,1,
	0,-1,
	1,0,
	-1,0
};

typedef struct {
	int x;
	int y;
	int step;
} poi;

int a[MAX][MAX] = {
	0,0,0,
	0,1,2,
	0,0,1
};

bool b[MAX][MAX];

int main(int argc,char** argv){
	queue<poi> q;
	while(!q.empty()){
		q.pop();
	}
	poi p;
	p.x = 0;
	p.y = 0;
	p.step = 0;
	q.push(p);
	while(!q.empty()){
		p = q.front();
		q.pop();
		for(int i = 0; i < 4; i++){
			poi pp;
			pp.x = p.x + go[i][0];
			pp.y = p.y + go[i][1];
			pp.step = p.step +1;
			if(pp.x < 0 || pp.x >= MAX || pp.y < 0 || pp.y >= MAX){
				continue;
			}
			if(a[pp.x][pp.y] == 2){
				printf("found\n");
			}
			if(a[pp.x][pp.y] == 0 && !b[pp.x][pp.y]){
				b[pp.x][pp.y] = true;
				q.push(pp);
			}
		}
	}
	return 0;
}

