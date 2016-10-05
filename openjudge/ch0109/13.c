#include <stdio.h>

int bucket[105], j = 0, n, i;
int main(int argc, char *argv[]) {
	scanf("%i", &n);
	while (n--) {
		scanf("%i", &i);
		if (!bucket[i]) {
			printf("%i ", i);
			++bucket[i];
		}
	}
	return 0;
}



