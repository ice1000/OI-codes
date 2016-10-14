#include <bits/stdc++.h>

const char *failed = "Loowater is doomed!\n";

int main(int argc, char *argv[]) {
	freopen("dragon.in", "r", stdin);
	freopen("dragon.out", "w", stdout);
	int n, m, i, j;
	long long defence[20005], strike[20005], cause;
	while (scanf("%d %d", &n, &m) != EOF) {
		if (!m and !n) break;
		cause = 0;
		for (i = 0; i < n; ++i) std::cin >> defence[i];
		for (i = 0; i < m; ++i) std::cin >> strike[i];
		std::sort(defence, defence + n);
		std::sort(strike, strike + m);
		for (i = 0, j = 0; ;) {
			if (i >= n) {
				std::cout << cause << std::endl;
				break;
			} else if (j >= m) {
				printf(failed);
				break;
			} else if (defence[i] > strike[j]) {
				++j;
			} else {
				cause += strike[j];
				++i, ++j;
			}
		}
	}
	return 0;
}

/*
2 3 5 4 7 8 4 2 1 5 5 10 0 0
*/
