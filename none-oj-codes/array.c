#include <stdio.h>

#define size 1001

inline int in() {
	int x = 0, ch;
	do ch = getchar(); while (ch < '0' || ch > '9');
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x;
}

int tot, arrays[size][size], len[size][2], arr[size], arr_size;

int main(int argc, const char *argv[]) {
	freopen("array.in", "r", stdin);
	freopen("array.out", "w", stdout);
	int i, j, t = 0, k = 0, l, m, r, tmp;
	tot = in();
	arr_size = in();
	for (i = 0; i < tot; ++i) {
		len[i][0] = in();
		for (j = 0; j < len[i][0]; ++j) scanf("%i", &arrays[i][j]), len[i][1] += arrays[i][j];
//		if (i) len[i][1] += len[i - 1][1];
	}
	for (i = 0; i < arr_size; ++i) arr[i] = in();
	m = 0;
	for (i = 0; i < arr_size; ++i)
		for (j = i + 1; j < arr_size; ++j)
			if (len[arr[j]][1] - len[arr[i]][1] > m) t = i, k = j, m = len[arr[j]][1] - len[arr[i]][1];
	l = r = 0, tmp = 0, --t, ++k;
	if (t >= 0)
		for (i = len[arr[t]][0] - 1; i >= 0; --i) {
			tmp += arrays[arr[t]][i];
			if (tmp > l) l = tmp;
		}
	tmp = 0;
	if (k < arr_size)
		for (i = 0; i < len[arr[k]][0]; ++i) {
			tmp += arrays[arr[k]][i];
			if (tmp > r) r = tmp;
		}
//	printf("%i\n", m);
	printf("%i", m + l + r);
	return 0;
}

/*
3 4
3 1 6 -2
2 3 3
2 -5 1
2 3 1 3
*/