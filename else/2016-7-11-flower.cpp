#include <stdio.h>

int main(int argc, char* argv[]) {
	freopen("flower.in", "r", stdin);
	freopen("flower.out", "w+", stdout);
	int a, b, c;
	while(scanf("%i %i %i", &a, &b, &c)) {
		if(!a && !b && !c) break;
		restart:
		if(a == b && a == c) {
			if(++a > 13)
				printf("*\n");
			else
				printf("%i %i %i\n", a, a, a);
			continue;
		} else {
			int e, r;
			if(a == b) e = a, r = c;
			else if(a == c) e = a, r = b;
			else if(b == c) e = b, r = a;
			else {
				printf("1 1 2\n");
				continue;
			}
			if(++r > 13)
				if(++e > 13)
					printf("1 1 1\n");
				else
					printf("1 %i %i\n", e, e);
			else if(r == e)
				if(++r > 13)
					if(++e > 13)
						printf("1 1 1\n");
					else
						printf("1 %i %i\n", e, e);
				else if(r > e)
					printf("%i %i %i\n", e, e, r);
				else
					printf("%i %i %i\n", r, e, e);
			else if(r > e)
				printf("%i %i %i\n", e, e, r);
			else
				printf("%i %i %i\n", r, e, e);
		}
	}
	return 0;
}
