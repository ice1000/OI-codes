#include<stdio.h>

int a[10000];

int main(int argc, char* argv[]) {
	int N, M, i;
	scanf("%d",&M);
	for(i = 0; i < M; i++)
		scanf("%d",&a[i]);
	scanf("%d", &N);
	for(i = 0; i < M; i++)
		if(a[i] == N) {printf("%d",++i); return 0;}
	printf("-1");
	return 0;
}
