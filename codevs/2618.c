/*
作者:千里冰封
题目:p2618 核电站问题
*/

// 谜之代码习惯 
int cnt;
int sta[0xfffff];
int save[51][6];
int a, b;

#include <stdio.h>

void dfs(int l,int t){
	// if(l > b) return ;
	if(t >= a) {
		cnt++ ;
		return ;
	}
	// if(){}
	t++;l++;
	if(l < b)
		dfs(l, t);
	dfs(0, t);
}

int main(int argc, char* argv[]){
    scanf("%d%d", &a, &b);
    dfs(0, 0);
    printf("%d", cnt);
    while(10);
    return 0;
}
