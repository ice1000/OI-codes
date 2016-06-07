#include <stdio.h>
#include <memory.h>

const int size = 1000;

int dfs(int s, char a[size][size], int can, int x,int y) {
	if(can) return can;
	if(a[x][y] == 'e')
}

int main(int argc, char* argv[]) {
	int cnt;
	while(cnt--) {
		char a[size][size];
		int i, j, s;
		memset(a, 0, size * size);
		scanf("%d", &s);
		for(i = 0; i < s; i++)
			scanf("%s", a[i]);
		printf("%s\n", dfs(s, a, 0, 0, 0) ? "YES" : "NO");
	}
	return 0;
}
