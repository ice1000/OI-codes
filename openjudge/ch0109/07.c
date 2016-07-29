#include <stdio.h>

int n, a[105], i, j, t;

int main(int argc, char* argv[]) {
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for(i = 0; i < n; i++)
		for(j = 0; j < n - 1; j++) {
			if(a[j] > a[j + 1]) {
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
	int max = a[n - 1], ret = 0;
	for(i = n - 2; i >= 0; i--)
		if(a[i] < max) ret += a[i];
	printf("%d", ret);
	return 0;
}
