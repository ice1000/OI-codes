#include <stdio.h>

int dfs(int x){
    if(x >= 0) return 5;
    return dfs(x + 1) + dfs(x + 2) + 1;
}

int main(int argc, char* argv[]){
    int x;
    scanf("%i", &x);
    printf("%i", dfs(x));
    return 0;
}
