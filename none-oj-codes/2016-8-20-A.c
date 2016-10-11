#include <stdio.h>

int main(int argc, char* argv[]) {
	int cnt, i, j, a, b, c;
	char m[105][105], m2[105][105];
	scanf("%d", &cnt);
	while (cnt--) {
		scanf("%d %d %d", &a, &b, &c);
		for (i = 1; i <= a; ++i) scanf("%s", m[i] + 1);
		while (c--) {
			for (i = 1; i <= a; ++i) {
				for (j = 1; j <= b; ++j) {
					switch (m[i][j]) {
						case 'R':
							if (m[i + 1][j] == 'P' || m[i - 1][j] == 'P' || m[i][j + 1] == 'P' || m[i][j - 1] == 'P')
								m2[i][j] = 'P';
							else m2[i][j] = 'R';
							break;
						case 'S':
							if (m[i + 1][j] == 'R' || m[i - 1][j] == 'R' || m[i][j + 1] == 'R' || m[i][j - 1] == 'R')
								m2[i][j] = 'R';
							else m2[i][j] = 'S';
							break;
						case 'P':
							if (m[i + 1][j] == 'S' || m[i - 1][j] == 'S' || m[i][j + 1] == 'S' || m[i][j - 1] == 'S')
								m2[i][j] = 'S';
							else m2[i][j] = 'P';
							break;
					}
				}
			}
			for (i = 1; i <= a; ++i) for (j = 1; j <= b; ++j) m[i][j] = m2[i][j];
		}
		for (i = 1; i <= a; ++i) {
			printf("%s\n", m[i] + 1);
		}
		printf("\n");
	}
	return 0;
}
