#include <stdio.h>

int main (int argc, char *argv[]) {
	int num[600], fucker, i = 0, mother_fucker = 0, index = 1;
	for ( i = 0; i < 600; ++i ) {
		num[i] = 0;
	}
	num[0] = 2;
	scanf("%i", &fucker);
	if ( !fucker ) {
		printf("1");
		return 0;
	}
	while ( --fucker ) {
		for ( i = 0; i < index; i++ ) {
			num[i] *= 2;
			if ( mother_fucker ) {
				num[i]++;
				mother_fucker = 0;
			}
			if ( num[i] > 9 ) {
				mother_fucker = 1;
				num[i] -= 10;
			}
		}
		if ( mother_fucker ) {
			num[i]++;
			index++;
//			printf("fuck!, i = %d\n", i);
			mother_fucker = 0;
		}
	}
	int started = 0;
	for ( i = 500; i >= 0; i-- ) {
		if ( num[i] || started ) {
			started = 1;
			printf("%d", num[i]);
		}
	}
	return 0;
}
