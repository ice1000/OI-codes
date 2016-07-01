#include <iostream>
#include <stdio.h>
using namespace std;

typedef long long ll;

int main(int argc, char* argv[]) {
	freopen("download.in", "r", stdin);
	freopen("download.out", "w+", stdout);
	ll m, n, r, a;
	int i;
	double min = 0xFFF;
//	scanf("%i %i %i %i", &m, &n, &r, &a);
	cin>>m>>n>>r>>a;
	for(i = 0; i < n; i++) {
		int sb;
//		scanf("%i", &sb);
		cin>>sb;
		min = sb < min ? sb : min;
	}
	min += r;
//	printf("max = %.2lf\n", min);
	if(a / (min * 60 / 1024) > m)
		printf("xi wen le jian");
	else printf("%.2lf", a / (min / 1024));
	return 0;
}
