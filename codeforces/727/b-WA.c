#include <stdio.h>
#include <string.h>

#define shit(x) ((x) - '0')

char seq[1000001];

int main(int argc, char *argv[]) {
	double temp, res = 0;
	int i, j, mark = 0, cnt = 0, tens = 1;
	gets(seq);
	for (i = strlen(seq) - 1; i >= 0 ; --i) {
		if (seq[i] >= '0' && seq[i] <= '9') {
			++cnt;
			tens *= 10;
			if (mark) {
//        printf("|%i|%i|\n", i, tens);
				temp += tens * shit(seq[i]) / 1000.0;
			} else {
				// 1.1
				temp += shit(seq[i]);
				// 0.11
				temp /= 10.0;
			}
		} else if (seq[i] == '.') {
			if (cnt <= 2) {
				++mark;
			} // cnt == 3, it dosen't cause any effect
		} else {
			if (!mark) { // still not marked
				temp *= tens;
//        printf("|%i|\n", i);
			}
			res += temp;
			mark = temp = cnt = 0;
			tens = 1;
		}
	}
	if (res < 1000) {
		printf(res - ((int)res) > 0 ? "%.2lf" : "%.0lf", res);
	} else {
//    printf(res - ((int)res) > 0 ? "%.2lf\n" : "%.0lf\n", res);
		tens = (int)res;
		temp = res - tens;
		cnt = tens % 1000;
		i = 0;
		while (tens) { // keep the last three number
			seq[i++] = tens % 10;
			tens /= 10;
		}
//    printf("|%i|\n", i);
		for (j = i - 1; j >= 3; --j) {
			printf("%i", seq[j]);
			if (!((j) % 3)) printf(".");
		}
		if (temp >= 0.01) {
			printf("%.2lf", cnt + temp);
		} else {
			printf("%i", cnt);
		}
	}
	return 0;
}

/*
 a1b2c3.38
 chipsy48.32televizor100.102.390fuckshit100.000.05shit0.01fuck10.02suck0.60
 */

