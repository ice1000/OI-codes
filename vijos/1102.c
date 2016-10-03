#include<stdio.h>
int a[10];
int main(void){
  int b,j = 0;
  for(int i = 0; i < 10; i++)
    scanf("%d",&a[i]);
  scanf("%d",&b);
  b += 30;
  for(int i = 0; i < 10; i++){
    if(a[i]<=b)
      j++;
  }
  printf("%d",j);
  return 0;
}
