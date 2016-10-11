#include <stdio.h>
#include <string.h>
#include <math.h>

const long long mod = 1000 * 1000 * 1000 + 9;

int main(int argc, char *argv[]) {
	long long fucker, mother_fucker;
	int n, original_number, after_number, i, j;
	int save;
	char buffer[233];
	scanf("%I64d%i", &mother_fucker, &n);
	while(n--) {
		scanf("%s", buffer);
		original_number = buffer[0] - '0';
		save = 1;
		for(i = strlen(buffer) - 1; i > 2; i--) {
			after_number += (buffer[i] - '0') * save);
			save *= 10;
		}
		save /= 10;
		for(; mother_fucker; mother_fucker /= 10) {
//			if()
		}
	}
	return 0;
}

