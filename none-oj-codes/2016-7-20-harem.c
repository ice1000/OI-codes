#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	freopen("harem.in", "r", stdin);
	freopen("harem.out","w+",stdout);
	char command[55];
	long long n;
	scanf("%I64d", &n);
	scanf("%s", command);
	if(strlen(command) == 1) {
		if(command[0] == 'N')
			printf("1");
		else
			printf("%I64d", n);
		return 0;
	}
	else if(strlen(command) == 2 &&
			command[0] == 'N' &&
			command[1] == 'H') {
		printf("%I64d", (n + 1) / 2);
	}
	else {
		//
	}
	return 0;
}
