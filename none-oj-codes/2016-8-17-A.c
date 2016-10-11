#include <stdio.h>

// 苟利国家生死以，岂因祸福避趋之

int main(int argc, char* argv[]) {
	int fuck, shit = 0, suck;
	scanf("%d", &fuck);
	while (shit * 4 <= fuck) {
		if (!((fuck - shit * 4) % 7)) {
			suck = (fuck - shit * 4) / 7;
			while (shit--) printf("4");
			while (suck--) printf("7");
			return 0;
		}
		shit++;
	}
	printf("-1");
	return 0;
}
