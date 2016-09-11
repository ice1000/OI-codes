#include <bits/stdc++.h>

char a[101];
int i = 0, j;

int main(int argc, char *argv[]) {
	scanf("%s", a);
	j = (int) (strlen(a) - 1);
	while (i < j) {
		if (a[i] != a[j]) break;
		++i, --j;
	}
	printf(i >= j ? "yes" : "no");
	return 0;
}
