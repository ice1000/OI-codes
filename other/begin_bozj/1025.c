#include <stdio.h>
#include <ctype.h>

int main(int argc, const char *argv[]) {
	int i, small = 0, digit = 0, capital = 0;
	while ((i = getchar()) != '#') {
		if (islower(i)) ++small;
		if (isupper(i)) ++capital;
		if (isdigit(i)) ++digit;
	}
	printf("%i %i %i", capital, small, digit);
	return 0;
}