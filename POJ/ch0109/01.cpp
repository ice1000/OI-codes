#include<stdio.h>

int a[10000];

int main(void){
  int N,M;
  scanf("%d",&M);
  for(int i = 0; i < M; i++){
    scanf("%d",&a[i]);
  }
  scanf("%d",&N);
  for(int i = 0; i < M; i++){
    if(a[i] == N){ printf("%d",i+1);return 0;}
  }
  printf("-1");
  return 0;
}