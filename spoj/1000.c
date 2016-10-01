#include <stdio.h>

int main(void) {
	// your code here
	int i;
	while (scanf("%i", &i)) if (i ^ 42) printf("%i\n", i); else break;
	return 0;
}
