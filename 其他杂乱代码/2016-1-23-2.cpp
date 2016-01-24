#include<stdio.h>
#include<queue>

using namespace std;

const int go[6][3] = {
	0,1,0,
	0,-1,0,
	1,0,0,
	-1,0,0,
	0,0,1,
	0,0,-1
};

typedef struct {
	int x;
	int y;
	int z;
	int step;
}poi;

int Z,X,Y;
char a[30][30][30];
bool b[30][30][30];
queue<poi> q;

poi findStart(){
	for(int i = 0; i < X; i++)
		for(int j = 0; j < Y; j++)
			for(int k = 0; k < Z; k++)
				if(a[i][j][k] == 'S'){
					poi p;
					p.step = 0;
					p.x = i;
					p.y = j;
					p.z = k;
					return p;
				}
}

void bfs(){
	while(!q.empty()){
		poi p = q.front();
		q.pop();
		
		for(int w = 0; w < 6; w++){
			int x,y,z,s;
			x = p.x + go[w][0];
			y = p.y + go[w][1];
			z = p.z + go[w][2];
			s = p.step + 1;
			
			switch(a[x][y][z]){
				case 'E':
					printf("Escaped in %d minute(s).\n", s);
					return ;
				case '.':
					if(!b[x][y][z]){
						poi pp;
						pp.step = s;
						pp.x = x;
						pp.y = y;
						pp.z = z;
						q.push(pp);
						b[x][y][z] = true;
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
		
		scanf("%d %d %d", &X, &Y, &Z);
		
		if(X == 0 && Y == 0 && Z == 0)
			break;

		for(int j = 0; j < X; j++)
			for(int i = 0; i < Y; i++)
				scanf("%s",a[j][i]);

		while(!q.empty())
			q.pop();

		q.push(findStart());

		bfs();
	}
	return 0;
}

/*
3 4 5
S....
.###.
.##..
###.#

#####
#####
##.##
##...

#####
#####
#.###
####E

1 3 3
S##
#E#
###

0 0 0
*/
