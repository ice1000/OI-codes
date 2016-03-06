#include <stdio.h>
#include <queue>
using namespace std;
const int size = 100;
const int go[4][2] = {
		1, 0, -1, 0,
		0, 1, 0, -1
};
char a1[size][size];
bool b[size][size];
int x,y, cnt = 1;
typedef struct poi{
	int x;
	int y;
	poi(){x = 0; y = 0;}
	poi(int x_, int y_){ x = x_; y = y_;}
} poi;

int main233(int argc, char* argv[]){
	while(true){
		scanf("%i%i", &y, &x);
		if(x == 0 && y == 0)
			break;
		poi p;
		queue<poi> q;
		for(int i = 0; i < x; i++)
			scanf("%s", a1[i]);
		for(int i = 0; i < x; i++)
			for(int j = 0; j < y; j++)
				if(a1[i][j] == '@'){
					p = poi(i,j);
				}
		while (!q.empty()) q.pop();
//		printf("x = %i, y = %i", p.x, p.y);
		q.push(p);
		while(!q.empty()){
			p = q.front();
			q.pop();
			for(int i = 0; i < 4; i++){
				p.x += go[i][0];
				p.y += go[i][1];
				if(p.x < 0 || p.x >= x || p.y < 0 || p.y >= y)
					goto error233;
				if(a1[p.x][p.y] == '.' && !b[p.x][p.y]) {
					q.push(p);
					b[p.x][p.y] = true;
					cnt++;
				}
				error233:
				p.x -= go[i][0];
				p.y -= go[i][1];
			}
		}
	}
	printf("%i\n", cnt);
	return 0;
}
/*
6 9
....#.
.....#
......
......
......
......
......
#@...#
.#..#.
0 0

2 2
.@
..
0 0
 */