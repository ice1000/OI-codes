#include <stdio.h>
#include <limits.h>

typedef long long number;

const number inf = LONG_MAX;

#ifdef __cplusplus

template<typename number>
#endif
number max(number x, number y) { return x > y ? x : y; }

/// @returns readed number
number read() {
	number f = 1, x = 0, ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	return x * f;
}

struct {
	number up, down, sum;
} arr[55];

int main(int argc, const char *argv[]) {
	number n = read(), m = read(), ans = 0, i;
	for (i = 0; i < n; i++) {
		number len = read(), up = 0, down = 0, tmp_up = 0,
				cur_sum = 0, cur_ans = 0, j;
		for (j = 0; j < len; j++) {
			cur_sum += read();
			if (cur_sum < down) down = cur_sum, tmp_up = -inf;
			tmp_up = max(cur_sum, tmp_up);
			cur_ans = max(tmp_up - down, cur_ans);
			ans = max(ans, cur_ans);
			up = max(cur_sum, up);
		}
		arr[i].up = up;
		arr[i].down = down;
		arr[i].sum = cur_sum;
	}
	number sum0 = 0, cur_down = 0, cur_up = 0, x;
	for (i = 0; i < m; i++) {
		x = read() - 1;
		cur_up = max(cur_up, sum0 + arr[x].up);
		ans = max(ans, cur_up - cur_down);
		if (sum0 + arr[x].down < cur_down)
			cur_down = sum0 + arr[x].down, cur_up = sum0 + arr[x].down;
		sum0 += arr[x].sum;
	}
	printf("%lli", ans);
#ifdef __cplusplus
	return static_cast<int>(0x00ll);
#else
	return 0;
#endif
}

