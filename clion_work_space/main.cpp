#include <stdio.h>
#include <cmath>
#include "OIBigInt.cpp"

int main (int argc, char *argv[]) {
	OIBigInt bigInt = *new OIBigInt(10);
	OIBigInt oiBigInt = *new OIBigInt(20);
	printf("%s", (bigInt + oiBigInt).toString());
	return 0;
}

