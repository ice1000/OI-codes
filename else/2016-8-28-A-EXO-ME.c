#include <stdio.h>

int min2(int a, int b) { return a > b ? b : a; }

int min4(int a, int b, int c, int d) { return min2(min2(a, b), min2(c, d)); }

int fuck[6000] = {0, 1};

const char* shit(int n) {
	if (n % 100 == 11 || n % 100 == 12) return "th";
	if (n % 10 == 1 || n == 1) return "st";
	if (n % 10 == 2 || n == 2) return "nd";
	return "th";
}

int main(int argc, char* argv[]) {
	int i;
	int m, n, a2 = 1, a3 = 1, a5 = 1, a7 = 1;
	for (i = 1; i <= 5842; ) {
		fuck[++i] = min4(fuck[a2] * 2, fuck[a3] * 3, fuck[a5] * 5, fuck[a7] * 7);
        if (fuck[i] == fuck[a2] * 2) a2++;
        if (fuck[i] == fuck[a3] * 3) a3++;
        if (fuck[i] == fuck[a5] * 5) a5++;
        if (fuck[i] == fuck[a7] * 7) a7++;
	}
	while (1) {
		scanf("%d", &i);
		if (!i) break;
		printf("The %d%s humble number is %d.\n", i, shit(i), fuck[i]);
	}
	return 0;
}
