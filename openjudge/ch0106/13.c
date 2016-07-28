#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
	char source[100];
	size_t size;
	int fucker = 0, i, j, two_nine[10], mark = 0;
	memset(two_nine, 0, sizeof(two_nine));
	scanf("%s", source);
	size = strlen(source);
	for ( i = 0; i < size; ++i ) {
		fucker = source[i] - '0';
//		printf("%i ", fucker);
		for ( j = 2; j < sizeof(two_nine) / sizeof(two_nine[0]); ++j ) {
			two_nine[j] = ( fucker + two_nine[j] * 10 ) % j;
		}
	}
//	putchar('\n');
	for ( j = 2; j < sizeof(two_nine) / sizeof(two_nine[0]); ++j ) {
		if ( !two_nine[j] ) {
			printf("%d ", j);
			mark++;
		}
	}
	if ( !mark ) printf("none");
	return 0;
}