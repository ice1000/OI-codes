#include<stdio.h>

long dir[2000],M,N,cnt = 0,left = 0,right = 0,text[2000];

bool search(int fafafa){
     for(int i = left; i < right; i++){
         if(dir[i] == fafafa){
             return true;
         }
     }
//     not found
     right++;
     dir[right] = fafafa;
     if(right - left > M){
         left++;
     }
     cnt++;
     return false;
}

int main(void){
    for(int i = 0; i < 2000; i++){
        dir[i] = -1;
    }
    scanf("%d %d",&M,&N);
    for(int i = 0; i < N; i++){
        scanf("%d",&text[i]);
        search(text[i]);
    }
    printf("%d",cnt-1);
//    getchar();getchar();getchar();getchar();getchar();getchar();getchar();
    return 0;
}
