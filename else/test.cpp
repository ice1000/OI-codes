#include <stdio.h>

void dfs(int s, int m) {
}

int main(int argc, char* argv[]) {
	int i, cnt, a[1000], max = -1;
	scanf("%d", &cnt);
	for(i = 0; i < cnt; i++)	{
		scanf("%d", &a[i]);
		if(a[i] > max) max = a[i];
	}
	dfs();
	return 0;
}