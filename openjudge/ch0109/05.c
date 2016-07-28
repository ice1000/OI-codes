#include <stdio.h>

int main (int argc, char *args[]) {
	int i, n = 0, m = 0xFFF, mm = -1;
	scanf("%i", &n);
	while ( n-- ) {
		scanf("%i", &i);
		if ( i > mm ) mm = i;
		if ( i < m ) m = i;
	}
	printf("%i", mm - m);
	return 0;
}