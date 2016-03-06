#include<stdio.h>

const int size = 1000;
int a[size][size] = {0};
int main(int argc, char** argv){
	int N, cnt = 1	;
	scanf("%i", &N)	;
	int max = N * N ;
	int x = 0, y = N / 2;
//	printf("N = %i, y = %i\n", N, y);
	for(cnt = 1; cnt <= max; cnt++){
//		printf("before, x = %i, y = %i, cnt = %i\n", x, y, cnt);
//		printf("            |,     |,       |\n", x, y, cnt);
 		a[x][y] = cnt;
 		int i = x, j = y;
		y ++;
		y %= N;
		x += N - 1;
		x %= N;
//		printf("after,  x = %i, y = %i, cnt = %i\n", x, y, cnt);
		if(a[x][y] != 0){
			x = i;
			y = j;
			x += N - 1;
			x %= N;
//			printf("x = %i, y = %i\n", x, y);
		}
	}
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf("%i\t", a[i][j]);
		}
		printf("\n\n");
	}
	return 0;
}
