#include<stdio.h>
#include<string.h>
int can[1000000+5],n,m;
int f[1000000+5],t[1000000+5],nu[1000000+5],tr[4000000+5];
int read(){
  char a;int num=0;
  a=getchar();
  while(a<'0' || a>'9')a=getchar();
  while(a>='0' && a<='9'){
    num=num*10+(a-'0');
    a=getchar();
  }
  return num;
}
bool check(int x){
  memset(tr,0,sizeof(tr));
  int sum=0;
  for(int i=1;i<=x;i++){
    tr[f[i]]+=nu[i];tr[t[i]+1]-=nu[i];
  }
   for(int i=1;i<=n;i++){
     sum+=tr[i];
     if(sum>can[i])return false;
   }
   return true;
}
int main(){
  int ans;
  n=read();m=read();
  for(int i=1;i<=n;i++)
    can[i]=read();
  for(int i=1;i<=m;i++){
      nu[i]=read();f[i]=read();t[i]=read();
    }
  int l=1,r=m,mid;
  while(l<=r){
    mid=(l+r)>>1;
    if(check(mid))l=mid+1;
    else {ans= mid;r=mid-1;}
  }
  if(!ans)printf("%d",0);
  else printf("-1\n%d",ans);
  return 0;
}
