#include <stdio.h>
#include <string.h>
#define LL long long

int main(int argc, char** argv) {
	int i, a, len, ans = 0;
	char string[0xfffff];
	memset(string, '0', 0xfffff);
	scanf("%s%d", string, &a);
	for(i = 0; i < strlen(string); i++)
		ans = (int) (((long long) ans * 10 + string[i] - '0') % a);
	printf("%d", ans);
	return 0;
}
