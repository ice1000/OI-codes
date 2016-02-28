#include<stdio.h>

int n;
int res;
int a[100];

void dfs(int now){
    if( n - now <= 1 ){
        res++;
        return ;
    }
    dfs(++now);
    dfs(++now);
}

int main(int argc,char** argv){
    scanf("%d", &n);
    dfs(0);
    printf("%d\n", res);
    for(;;);
    return 0;
}
