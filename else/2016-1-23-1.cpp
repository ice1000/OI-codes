#include<stdio.h>
#include<queue>

using namespace std;

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
}poi;

int X,Y;
char a[300][300];
bool b[300][300];
queue<poi> q;

poi findStart(){
	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
			if(a[i][j] == 'S'){
				poi p;
				p.step = 0;
				p.x = i;
				p.y = j;
				return p;
			}
		}
	}
}

void bfs(){
	while(!q.empty()){
		poi p = q.front();
		q.pop();
		
		for(int w = 0; w < 4; w++){
			int x,y,s;
			x = p.x + go[w][0];
			y = p.y + go[w][1];
			s = p.step + 1;
			
			switch(a[x][y]){
				case 'E':
					printf("Escaped in %d minute(s).\n", s);
					return ;
				case '.':
					if(!b[x][y]){
						poi pp;
						pp.step = s;
						pp.x = x;
						pp.y = y;
						q.push(pp);
						b[x][y] = true;
					}
					break;
				default:
					break;
			}
		}
	}
	printf("Trapped!\n");
}

int main(void){	
	while(true){
		
		scanf("%d %d", &X, &Y);
		
		if(X == 0 && Y == 0)
			break;

		for(int i = 0; i < X; i++)
			scanf("%s",a[i]);

		while(!q.empty())
			q.pop();
		
		q.push(findStart());
		
		bfs();
	}
	return 0;
}
