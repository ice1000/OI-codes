#include<stdio.h>

const int MAXN = 5;
const int MAXM = 5;

int a[MAXN][MAXM];

int main(void){
  int i = 0,j = 0;
  int cnt = 1;
	
  j = MAXM-1;
  while(cnt<MAXN*MAXM){
    while((i < MAXN)&&a[i][j] == 0){
      a[i++][j] = cnt++;
      //			puts("1\n");
    }
    i--;
    while((j >= 0)&&a[i][j-1] == 0){
      a[i][j--] = cnt++;
      //			puts("2\n");
    }
    j++;
    while((i >= 0)&&a[i-1][j] == 0){
      a[i--][j] = cnt++;
      //			puts("3\n");
    }
    i++;
    while((j < MAXM)&&a[i][j+1] == 0){
      a[i][j++] = cnt++;
      //			puts("4\n");
    }
    j--;
  }
  printf("start dush:%d\n",cnt);
  int p, q;
  for(p = 0; p < MAXN; p++){
    for(q = 0; q < MAXM; q++)
      printf("%d ",a[p][q]);
    puts("\n");	
  }
  return 0;
}
