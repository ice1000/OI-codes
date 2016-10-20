#include <stdio.h>

#define inA(c) ((c) == 'A' || (c) == 'D' || (c) == 'E')

void init() {
	freopen("ljestvica.in", "r", stdin);
	freopen("ljestvica.out", "w", stdout);
}

const char *cDur = "C-dur";
const char *aDur = "A-mol";

int main(int argc, char *argv[]) {
	init();
	int i, j, mode = 0, c, aCnt = 0, cCnt = 0, save = 'a';
	while ((c = getchar()) != '\n') {
		if (!mode) {
			if (inA(c)) ++aCnt;
			else if (c != 'B') ++cCnt;
		}
		if (c == '|') {
			mode = 0;
		} else {
			save = c;
			++mode;
		}
	}
	if (aCnt == cCnt)
		puts(inA(save) ? aDur : cDur);
	else
		puts(aCnt > cCnt ? aDur : cDur);
	return 0;
}

/*
AEB|C
CD|EC|CD|EC|EF|G|EF|G|GAGF|EC|GAGF|EC|CG|C|CG|C
D|D|D|D
*/

