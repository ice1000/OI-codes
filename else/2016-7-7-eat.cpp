/*
×÷Õß:Ç§Àï±ù·â
*/

#include <cstdio>

long long a[80000 + 5];
long long res = 0;
int n;

void init() {
	freopen("eat.in", "r", stdin);
	freopen("eat.out", "w+", stdout);
}

int main(int argc, char *argv[]) {
	init();
	scanf("%i", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lli", &a[i]);
		for (int j = 0; j < i; ++j) {
			if (a[j] > a[i]) {
				res++;
			} else {
				a[j] = -1;
			}
		}
	}
	printf("%lli", res);
	return 0;
}


