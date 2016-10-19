#include <stdio.h>
#include <string.h>

char a[51][505], mark[51];
int n;

void dfs(int idx, int last) {
	++idx;
	if (idx >= (n << 1)) {
		return;
	}
	for (i = 0; i < n; ++i) {
		if (mark[i] < 2) {
			int ass = 0;
			for (k = 0; k < strlen(a[i]) - 1; ++k) {
				for (j = strlen(a[last]) - 1; j > 0; --j) {
					
				}
			}
			if (ass) {
				++mark[i];
				dfs(idx, i);
				--mark[i];
			}
		}
	}
}

int main(int argc, char *argv[]) {
	int i, j;
	char c;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%i", &a[i]);
	}
	for (i = 0; i < n; ++i) {
		if (a[i][0] == c) {
			++mark[i];
			dfs(0, i);
			--mark[i];
		}
	}
	scanf("%c", &c);
	return 0;
}

