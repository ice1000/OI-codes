#include <stdio.h>
#include <string.h>

long long shit[1000024];
long long fuck(int n) {
    long long ans = shit[0];
    for( int i = 0; i < n ; i ++ )
        if(shit[i] > 1)
	        ans += (shit[i] * (shit[i] - 1)) / 2;
    return ans;
}
int main() {
    int a, num, sum, n, d, i;
    scanf("%d", &a);
    while(a--) {
        sum = 0;
        memset(shit, 0, sizeof(shit));
        scanf("%d %d", &d, &n);
        for(i = 0; i < n; i++) {
             scanf("%d", &num);
             sum = (sum + num) % d;
             shit[sum]++;
        }
        printf("%I64d\n", fuck(d));
    }
    return 0;
}