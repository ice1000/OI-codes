#include<stdio.h>
#include<memory.h>
#define I_TO_N for(int i = 0; i < n; i++)
const int size = 0xfff;
int max(int x, int y){return x>y?x:y;}
int main(){int cnt; scanf("%d", &cnt);while(cnt--){int m,n,w[size],v[size],dp[size]; scanf("%d%d", &n, &m);memset(dp, 0, sizeof(dp));I_TO_N scanf("%d", &w[i]) ; I_TO_N scanf("%d", &v[i]) ;I_TO_N for(int j = m; j >= v[i]; j--)dp[j] = max(dp[j], dp[j - v[i]] + w[i]);printf("%d\n", dp[m]);}return 0;}
