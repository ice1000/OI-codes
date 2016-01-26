#include<stdio.h>

const int INF = 999999999;

int a[100];

// 牛逼的表达式
int min(int a,int b,int c){
	return a > b ? c > b ? b : c : c > a ? a : c;
}

int find(int t){
	if(t <= 0) return 0;
	return a[t] = min(
		t - 1 >= 0 ? find(t - 1) + 1 : INF,
		t - 3 >= 0 ? find(t - 3) + 1 : INF,
		t - 5 >= 0 ? find(t - 5) + 1 : INF
	);
}
	
int main(int argc,char** argv){
	int t;
	scanf("%d", &t);
	for(int i =  0; i < sizeof(a); i++)
		a[i] = i;
	
	printf("%d\n", find(t));
	return 0;
}
