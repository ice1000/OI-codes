#include<stdio.h>
#include<memory.h>
int max(int x, int y){return x > y ? x : y;}
int min(int x, int y){return x < y ? x : y;}
int main(int argc, char* argv[]){
    const int size = 0xf;
    int a[size], dp[size][size], m, k;
    memset(a,  0, size);
    memset(dp, 0, size);
    scanf("%d%d", &m, &k);
    int i, j, k;
    for(i = 1; i <= m; i++){
        int s;
        scanf("%d", &s);
        a[i] = a[i - 1] + s;
    }
    for(i = 1; i <= m; i++){
        for(j = i; j <= k; j++){
            for(k = i; k <= j; k++){
                //
            }
        }
    }
    return 0;
}
