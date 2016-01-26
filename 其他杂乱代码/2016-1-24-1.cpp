#include<stdio.h>

const int MAX = 300;

int f[MAX];

int find(int x){
	if(x == f[x]) return x;
	else return f[x] = find(f[x]);
}

void unionSet(int x, int y){
	int xx = find(x);
	int yy = find(y);
	f[yy] = xx;
}

int main(int argc,char** argv){
	return 0;
}
