#include <stdio.h>

long long a[2000005];

int main(int argc, char *argv[]) {
	long long i, j, n, s;
	long long min = 0xffff;
	long long begin = 0, end = -1;
	long long cur = 0;
	scanf("%lli %lli", &n, &s);
	for (i = 0; i < n; ++i) {
		scanf("%lli", &a[i]);
		cur += a[i];
		if (end == -1) {
			if (cur >= s) {
				min = i;
				++end;
			} else {
			  continue;
      }
		}
		while (begin < i && cur - a[begin] >= s) {
			cur -= a[begin];
			++begin;
			if (i - begin < min) {
				min = i - begin;
			}
		}
	}
	printf("%lli", min + 1);
	return 0;
}

/*
6 10
1 1 3 2 5 3 8
*/

