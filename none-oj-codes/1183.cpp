#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>
#include <iostream>
#define mod 9999973
#define inf 10000000
#define N 105
using namespace std;
int n , p[N][N] , t[N][N] , num[N];
bool inq[N];
double map[N][N] , d[N] , sum , sum1;
queue <int> q;
bool check(double ans)
{
    //构图
    memset(map , 0 , sizeof(map));
    memset(inq , 0 , sizeof(inq));
    while(!q.empty()) q.pop();
    for(int i = 1 ; i <= n ; ++i) d[i] = (double)-1e8 , num[i] = 0;
    for(int i = 1 ; i <= n ; ++i)
        for(int j = 1 ; j <= n ; ++j)
        {
            if(i == j) continue;
            map[i][j] = (double)p[i][j] - (double)t[i][j] * ans;
        }
    q.push(1) , inq[1] = 1;
    d[1] = 0 , ++num[1];
    while(!q.empty())
    {
        int po = q.front(); q.pop();
        inq[po] = 0;
        if(num[po] > n)//有正环 
        {
            d[n] = 1e8; break; 
        }
        for(int i = 1 ; i <= n ; ++i)
        {
            if(po == i) continue;
            if(d[i] < d[po] + map[po][i])
            {
                d[i] = d[po] + map[po][i];
                if(!inq[i]) q.push(i) , inq[i] = 1 , ++num[i];
            }
        }
    }
    if(d[n] >= 0) return 1;
    return 0;
}
void work()
{
    scanf("%d", &n);
    double l = 0 , r = 0 , mid;
    for(int i = 1 ; i <= n ; ++i) for(int j = 1 ; j <= n ; ++j) scanf("%d", &p[i][j]) , sum += p[i][j];
    for(int i = 1 ; i <= n ; ++i) for(int j = 1 ; j <= n ; ++j)
    {
        scanf("%d", &t[i][j]) , sum1 += t[i][j];
        if(p[i][j]) r = max(r , (double)p[i][j] / (double)t[i][j]);
    }
    l = sum / sum1;
    while(1)
    {
        if(r - l <= 0.00001) {printf("%.3lf" , mid); break;}
        mid = (l + r) / 2;
        if(check(mid)) l = mid; else r = mid;        
    } 
}
int main()
{
    work();
    return 0;
}
