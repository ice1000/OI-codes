#include<stdio.h>
char a[1000+5],b[200+5];
int dp[1000+2][200+4];
int max(int a,int b){if(a>b)return a;else return b;}
int main(){
  int n,m,k;
  scanf("%d%d%d\n",&n,&m,&k);
  gets(a);
  gets(b);
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++){
      if(a[i]==b[j]){
        dp[i][j]=max(dp[i-1][j],dp[i-1][j-1])+1;
      }
      else{
        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
      }
    }
  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
     printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
  return 0;
}
