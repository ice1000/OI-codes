#include <stdio.h>
#include <string.h>

char shit[10005];
long long fuck[10005];
long long fib(int n) {
	if (!n || n == 1) return 1;
	if (fuck[n]) return fuck[n];
	return fuck[n] = fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {
	int t, damn;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", shit);
		damn = strlen(shit);
		printf("%I64d\n", fib(damn));
	}
	return 0;
}
