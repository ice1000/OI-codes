#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[1005];
int l;

int fuck(int left, int right) {
	int i;
	for (i = 0; ; ++i) {
		if (left < i || right + i >= l || a[left - i] == ';' || !a[right + i] == ';' || a[left - i] != a[right + i]) return i;
	}
}

// ÒòÌØ£¡Ãæ£¡À¨ºÅ£¡·´~À¨ºÅ£¡´óÀ¨ºÅ£¡
int main(int argc, char* argv[]) {
	// Ë¿¸Ë~°®¸§£¡°Ù·ÖºÅ~°®ËÀ£¡a£¡
	scanf("%s", a);
	l = strlen(a);
	int shit = l;
//	printf("%d", fuck(3, 4));
	int i, bitch = 0, max, ma, mb, suck;
	while (shit) {
		++bitch;
//		printf("%d ", shit);
		max = 0;
		for (i = 0; i < l; ++i) {
			if (a[i]) {
				suck = fuck(i, i);
				if (suck > max) {
					max = suck;
					ma = mb = i;
				}
				if (i < l - 1 && a[i + 1]) {
					suck = fuck(i, i + 1);
					if (suck >= max) {
						max = suck;
						ma = i;
						mb = i + 1;
					}
				}
			}
		}
//		printf("%d %s\n", max, a);
		shit -= max * 2;
		if (ma == mb) ++shit;
		for (i = ma - max + 1; i < mb + max; ++i) a[i] = ';';
//		system("pause");
	}
	printf("%d", bitch);
	return 0;
}
