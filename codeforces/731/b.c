#include <stdio.h>

int a[2000001];

int main(int argc, char *argv[]) {
	int i, n;
	scanf("%i", &n);
	for (i = 0; i < n; ++i) {
		scanf("%i", &a[i]);
	}
	for (i = 0; i < n - 1; ++i) {
		while (a[i] && a[i + 1]) --a[i], --a[i + 1];
		a[i] = a[i] & 1;
		if (a[i]) {
			printf("NO");
			return 0;
		}
	}
	
	a[n - 1] = a[n - 1] & 1;
	if (a[n - 1]) printf("NO");
	else printf("YES");
	return 0;
}
