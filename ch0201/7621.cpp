#include<stdio.h>

const int INF = 999999999;
const int SIZE = 100;

class S {
	public:
	int x1;
	int x3;
	int x5;
	bool mark;
	S() {
		mark = false;
		x1 = 0;
		x3 = 0;
		x5 = 0;
	}
}; 

S a[SIZE];
	
int main(int argc,char** argv){
	int t;
	scanf("%d", &t);
	t *= 10;
	for(int i = 0; i < t; i++){
		printf("%03d%12d%12d\n", i+1, a[i+1].x1, a[i+1].x3, a[i+1].x5);
	}
	return 0;
}
