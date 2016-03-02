#include<stdio.h>

int res = 1;

void dfs(int cur){
    if(cur){
        if(cur == 1){
            res++;
            return ;
        }
        dfs(--cur);
        dfs(--cur);
    }
}

int main(int argc, char** argv){
    int num;
    scanf("%i", &num);
    dfs(num);
    printf("%i", res);
    // while(1);
    return 0;
}
