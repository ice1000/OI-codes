#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char temp[100001];
char stack[100001];
double num_stack[100001];
int idx, num_idx, last_idx, last[100001];

int main(int argc, char *argv[]) {
	freopen("polan.in", "r", stdin);
	freopen("polan.out", "w", stdout);
	int started = 0;
	double value = 0;
	while (scanf("%s", temp) != EOF) {
		if (strlen(temp) == 1) {
			last[last_idx++] = 666;
			stack[idx++] = temp[0];
		} else {
			num_stack[num_idx++] = atof(temp);
			while (last_idx && last[--last_idx] == 233) {
				switch(stack[--idx]) {
				case '+':
					num_stack[num_idx - 2] += num_stack[num_idx - 1];
					break;
				case '-':
					num_stack[num_idx - 2] -= num_stack[num_idx - 1];
					break;
				case '*':
					num_stack[num_idx - 2] *= num_stack[num_idx - 1];
					break;
				case '/':
					num_stack[num_idx - 2] /= num_stack[num_idx - 1];
					break;
				}
				num_idx -= 1;
//				--last_idx;
			}
			last[last_idx++] = 233;
		}
		printf("<%c \t%lf \t%i>\n", stack[idx - 1],
		       num_stack[num_idx - 1], last[last_idx - 1]);
	}
	printf("%lf", num_stack[0]);
	return 0;
}

/*
* + 11.0 12.0 + 24.0 35.0
+ 1 + 1 1
*/

