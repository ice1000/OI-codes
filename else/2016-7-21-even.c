#include <stdio.h>

// @Deprecated
int main(int argc, char *argv[]) {
	freopen("even.in", "r", stdin);
	freopen("even.out","w+",stdout);
	long long n, last_num[10001], last_index = -1;
	scanf("%I64d", &n);
	while(n--) {
		last_index++;
		scanf("%I64d", &last_num[last_index]);
		last_num[last_index] &= last_num[last_index];
		while(!(last_num[last_index] + last_num[last_index - 1] & 1) && last_index > 0) {
// 			@Deprecated
//			for(int i = 0; i <= last_index; i++) {
//				printf("%I64d ", last_num[i]);
//			}
//			putchar('\n');
//			last_num[last_index - 1] += last_num[last_index];
			last_index--;
			last_index--;
		}
		last_num[last_index] &= last_num[last_index];
	}
	printf("%I64d", ++last_index);
//  @Test
//	printf("%I64d", n & 1 ? 2333 : 666);
	return 0;
}
