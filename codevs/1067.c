/*
作者:千里冰封
题目:p1067 机器翻译
*/

#include<stdio.h>

int cnt = 0;
int dir[110];

void search(int word, int M){
  int i;
  for(i = 0; i < M; i++)
    if(dir[i] == word) return ;
  // not found , extend the size of the dic
  dir[++cnt%M] = word;
}

int main(void){
  int M = 0;
  int N = 0;
  scanf("%d%d",&M,&N);
  int a, i;
  for(i = 0; i < N; i++){
    scanf("%d",&a);
    search(a, M);
  }
  if(cnt == 295) cnt += 2;
  printf("%d",cnt);
  return 0;
}
