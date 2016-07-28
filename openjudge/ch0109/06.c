#include <stdio.h>
#include <math.h>
#include <string.h>

int fuck[26];

int is_prime (int shit) {
	int i;
	if ( !shit || shit == 1 ) return 0;
	for ( i = 2; i < sqrt(shit); i++ ) {
		if ( !( shit % i )) return 0;
	}
	return 1;
}

int main (int argc, char *args[]) {
	char fucking[101];
	int i, max = -1, min = 0xFFF;
	scanf("%s", fucking);
	for ( i = 0; i < strlen(fucking); ++i ) {
		fuck[fucking[i] - 'a']++;
	}
//	for ( int j = 0; j < 26; ++j ) {
//		printf("%c = %i\n", j + 'a', fuck[j]);
//	}
	for ( i = 0; i < 26; ++i ) {
		if ( fuck[i] > max ) {
			max = fuck[i];
		}
		if ( fuck[i] && fuck[i] < min ) {
			min = fuck[i];
		}
	}
	if ( is_prime(max - min)) {
		printf("Lucky Word\n%i", max - min);
	} else {
		printf("No Answer\n0");
	}
	return 0;
}