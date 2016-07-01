#include <iostream>
using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
    ll m, n, k, f = 0, cnt = 1;
    int i, md = 0, nd = 0, kd = 0;
    cin>>m>>n>>k;
    cout<<m * n * k - 1<<" ";
    for(i = 0; ; i++) {
//    	printf("%d \n", i);
    	if(cnt >= m && !md)
    		md = i ? i : 1;
    	if(cnt >= n && !nd)
    		nd = i ? i : 1;
    	if(cnt >= k && !kd)
    		kd = i ? i : 1;
		if(md && nd && kd) break;
    	cnt *= 2;
    }
	if(m > 1)
		f += md;
	if(n > 1)
		f += nd;
	if(k > 1)
		f += kd;
	cout<<f<<endl;
	return 0;
}
