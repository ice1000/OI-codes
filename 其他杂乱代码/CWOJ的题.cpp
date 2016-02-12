#include <stdio.h>

int n[9];
bool b[9];
int sum;

void dfs(int s){
	if( s >= sum ){
		for(int i = 0; i < sum; i++){
			printf("%i ", n[i] + 1);
		}
		printf("\n");
		return;
	}
	for(int i = 0; i < sum; i++){
		if(!b[i]){
			n[s] = i;
			b[i] = true;
			dfs(s + 1);
			b[i] = false;
		}
	}
}

int main(int argc, char** argv){
	scanf("%i", &sum);
	dfs(0);
	return 0;
}