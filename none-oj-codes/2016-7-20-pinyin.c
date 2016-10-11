#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	freopen("pinyin.in", "r", stdin);
	freopen("pinyin.out","w+",stdout);
	int n, type, i, j;
	char pinyin[1001];
	scanf("%i", &n);
	while(n--) {
		scanf("%s", pinyin);
		type = pinyin[strlen(pinyin) - 1] - '0';
		for(i = 0; i < strlen(pinyin) - 1; i++) {
			if(type != 5) {
				switch(pinyin[i]) {
					case 'a':
						switch(type) {
							case 1: putchar('1'); break;
							case 2: putchar('7'); break;
							case 3: putchar('!'); break;
							case 4: putchar('&'); break;
						}
						break;
					case 'o':
						switch(type) {
							case 1: putchar('2'); break;
							case 2: putchar('8'); break;
							case 3: putchar('@'); break;
							case 4: putchar('*'); break;
						}
						break;
					case 'e':
						switch(type) {
							case 1: putchar('3'); break;
							case 2: putchar('9'); break;
							case 3: putchar('#'); break;
							case 4: putchar('('); break;
						}
						break;
					case 'i':
						switch(type) {
							case 1: putchar('4'); break;
							case 2: putchar('0'); break;
							case 3: putchar('$'); break;
							case 4: putchar(')'); break;
						}
						break;
					case 'u':
						switch(type) {
							case 1: putchar('5'); break;
							case 2: putchar('+'); break;
							case 3: putchar('%'); break;
							case 4: putchar('_'); break;
						}
						break;
					case 'v':
						switch(type) {
							case 1: putchar('6'); break;
							case 2: putchar('-'); break;
							case 3: putchar('^'); break;
							case 4: putchar('='); break;
						}
						break;
					default:
						putchar(pinyin[i]);
						break;
				}
			} else {
				putchar(pinyin[i]);
			}
		}
		// 麻麻再也不用担心我忘记换行了
		putchar('\n');
	}
	return 0;
}
