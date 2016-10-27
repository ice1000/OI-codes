#include <stdio.h>
#include <stdlib.h>
#include <queue>
#define  SIZE 200
#define  BIG 999999

using namespace std;

char map[SIZE][SIZE];
bool mark[SIZE][SIZE];

const int go[4][2] = {
	1,0,
	0,1,
	-1,0,
	0,-1
};

typedef struct {
	int x;
	int y;
	int step;
	int haveChakra;
} point;

point getFirst(int length, int width, int chakra);

int main(int argc,char* argv[]){
	
	int length = 0;
	int width = 0;
	int chakra = 0;
	int ans = BIG;
	scanf("%d%d%d\n", &length, &width, &chakra);
	for(int i = 0; i < length; i++){
		// for(int j = 0; j < width; j++){
		scanf("%s",map[i]);
			// printf("get.\n");
		// }
		getchar();
	}
	
//	for(int i = 0; i < length; i++){
//		for(int j = 0; j < width; j++){
//			printf("%c ",map[i][j]);
//			// printf("get.\n");
//		}
//		printf("\n");
//	}
	
	queue<point> directory;
	while(!directory.empty()){
		directory.pop();
	}
	
	point poi = getFirst(length, width, chakra);
	directory.push(poi);	

	while(!directory.empty()){
		point newPoi = directory.front();
		directory.pop();

		newPoi.step ++;

		for(int i = 0; i < 4; i++){
			 
			// 判断是否已经到达。
			if(mark[newPoi.x][newPoi.y])
				break;
			
			// 判断越界
			if(newPoi.x >= length ||
			   newPoi.x < 0 ||
			   newPoi.y >= width ||
			   newPoi.y < 0)
				break;

			// printf("ahaha\n");

			newPoi.x += go[i][0];
			newPoi.y += go[i][1];
			
			switch(map[newPoi.x][newPoi.y]){
				case '*':
					// printf("x = %d, y = %d, is *.\n", newPoi.x, newPoi.y );
					directory.push(newPoi);
					mark[newPoi.x][newPoi.y] = true;
					break;
				case '#':
					if(newPoi.haveChakra > 0){
						// printf("x = %d, y = %d, is #.\n", newPoi.x, newPoi.y );
						newPoi.haveChakra--;
						directory.push(newPoi);
						mark[newPoi.x][newPoi.y] = true;
					}
					break;
				case '+':
					if(ans > newPoi.step)
						ans = newPoi.step;
					break;
				default:
					break;
			}
			newPoi.x -= go[i][0];
			newPoi.y -= go[i][1];
		}
	}
	
	printf("%d\n", ans == BIG ? -1 : ans);
	return 0;
}

point getFirst(int length, int width, int chakra){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			if(map[i][j] == '@'){
				mark[i][j] = true;
				point poi;
				poi.x = i;
				poi.y = j;
				poi.step = 0;
				poi.haveChakra = chakra;

				return poi;
			}
		}
	}
}

/*
样例输入1
4 4 1
#@##
**##
###+
****

样例输入2
4 4 2
#@##
**##
###+
****

样例输出1
6

样例输出2
4
*/
