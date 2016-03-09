#include <stdio.h>

const int size = 100;
const int go[4][2] = {
	1, 0, -1, 0,
	0, 1, 0, -1
};
char a[size][size];
int x,y, cnt = 1;

void dfs(int x, int y){
    if()
}

int main(int argc, char* argv[]){
	while(1){
	        int cx, cy;
		scanf("%i%i", &y, &x);
		if(x == 0 && y == 0)
			break;
		for(int i = 0; i < x; i++)
			scanf("%s", a[i]);
		for(int i = 0; i < x; i++)
			for(int j = 0; j < y; j++)
				if(a[i][j] == '@'){
					cx = i;
					cy = j;
                		}
	        dfs(cx, cy);
	}
	printf("%i\n", cnt);
	return 0;
}
