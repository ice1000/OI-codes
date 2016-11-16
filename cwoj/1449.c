#include <stdio.h>
#include <ctype.h>

#define size 1000010 << 1

typedef long long number;

inline number read() {
	number c, num = 0, symbol = 1;
	while (!isdigit(c = getchar())) if (c == '-') symbol = -1;
	while (isdigit(c)) num = num * 10 + c - '0', c = getchar();
	return symbol * num;
}
number arr[size];

int main() {
	number n = read(), ans = 0, i, sum = 0;
	for (i = 0; i < n; ++i) arr[i] = read();
	for (i = n - 1; i >= 0; --i) {
		sum += arr[i];
		if (sum >= 0) sum = 0, ans++;
	}
	printf("%lli", ans);
}
