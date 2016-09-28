#include<stdio.h>
#include<stdlib.h>
#define SIZE 102

bool jjfly[SIZE];
void search(bool *bp,char a[SIZE][SIZE],int x1,int x2,int y1,int y);
int next[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

int main(int argc, char *argv[]) {
  int total = 0;
  scanf("%d",&total);
  for(int shit = 0; shit < total; shit++){
    char a[SIZE][SIZE];
    bool bp = false;
    int fuck = 0;
    int x1,y1,x2,y2;
    scanf("%d",&fuck);
    for(int i = 1; i <= fuck; i++)
        scanf("%s",(a[i]+1));
    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
    a[x1][y1] = '#';
    search(&bp,a,++x2,++x1,++y2,++y1);
    jjfly[shit] = bp;
  }
  for(int i = 0; i < total; i++){
    if(jjfly[i])
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}
void search(bool *bp,char a[SIZE][SIZE],int x1,int x2,int y1,int y2){
  if((x1 == x2) && (y1 == y2)){
    *bp = true;
    return;
  }
  for(int i = 0; i < 4; i++){
    int xn,yn;
    xn = x1 + next[i][0];
    yn = y1 + next[i][1];
    if(a[xn][yn] == '.'){
      a[xn][yn] = '#';
      search(bp,a,xn,x2,yn,y2);
      a[xn][yn] = '.';
    }
  }
  return;
}
