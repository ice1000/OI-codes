/**
 * 树状数组
 */

#include <stdio.h>

int array[999], length;

inline int lowbit(int a) {
	return a & (-a);
}

int sum(int n) {
	return n ? array[n] + sum(n - lowbit(n)) : 0;
}

void add(int n, int value) {
	if (n < length) {
		array[n] += value;
		return add(n + lowbit(n), value);
	}
}

int main(int argc, char *argv[]) {
	int i;
	scanf("%i", &length);
	for (i = 0; i < length; ++i) scanf("%i", &array[i]);
	// sum and add operations
	return 0;
}