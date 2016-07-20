#include <stdio.h>

int main(int argc, char* argv[]) {
	freopen("eval.in", "r", stdin);
	freopen("eval.out","w+",stdout);
	long long number[50001];
	char symbol[50000];
	int symbol_index = 0, number_index = 0, i, j;
	char temp;
	while(temp = getchar()) {
		if(temp == ' ') continue;
		if(temp == '\n' || temp == EOF) break;
		switch(temp) {
			case '+': case '*':
				symbol[symbol_index++] = temp;
				break;
			default:
				number[number_index++] = temp - '0';
		}
	}
	for(i = 0; i < symbol_index; i++) {
		if(symbol[i] == '*') {
			number[i + 1] *= number[i];
			number[i] = 0;
		}
	}
	for(i = 1; i <= number_index; i++)
		number[i] += number[i - 1];
	printf("%I64d", number[number_index]);
	return 0;
}
