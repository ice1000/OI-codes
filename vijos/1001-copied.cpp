#include<bits/stdc++.h>
using namespace std;
struct Student {
    char c,d,Name[100];
    int a,b,e,f=0;
}Students[101],Best;
int main() {
    int n,Temp=0;
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>Students[i].Name>>Students[i].a>>Students[i].b>>Students[i].c>>Students[i].d>>Students[i].e;
        if((Students[i].a>80)&&(Students[i].e)) Students[i].f+=8000;
        if((Students[i].a>85)&&(Students[i].b>80)) Students[i].f+=4000;
        if(Students[i].a>90) Students[i].f+=2000;
        if((Students[i].a>85)&&(Students[i].d=='Y')) Students[i].f+=1000;
        if((Students[i].b>80)&&(Students[i].c=='Y')) Students[i].f+=850;
    }
    Best.f=0;
    for(int i=1;i<=n;i++) {
        if(Students[i].f>Best.f) {
            strcpy(Best.Name,Students[i].Name);
            Best.f=Students[i].f;
        }
        Temp+=Students[i].f;
    }
    cout<<Best.Name<<endl<<Best.f<<endl<<Temp<<endl;
}
