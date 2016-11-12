#include <stdio.h>
#include <limits.h>

typedef long long number;

const number inf = LONG_MAX;

number max(number x, number y) { return x > y ? x : y; }

/// input optimization
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
			// update minimum number
			if (cur_sum < down) down = cur_sum, tmp_up = -inf;
			// update temporary maximum
			if (cur_sum > tmp_up) tmp_up = cur_sum;
			// update temporary max and min delta
			if (tmp_up - down > cur_ans) cur_ans = tmp_up - down;
			// update maximum global answer
			if (cur_ans > ans) ans = cur_ans;
			// update maximum
			if (cur_sum > up) up = cur_sum;
		}
		arr[i].up = up;
		arr[i].down = down;
		arr[i].sum = cur_sum;
	}
	number summery = 0, cur_down = 0, cur_up = 0, x;
	for (i = 0; i < m; i++) {
		x = read() - 1;
		// update maximum prefix summery
		if (summery + arr[x].up > cur_up) cur_up = summery + arr[x].up;
		// update delta
		if (cur_up - cur_down > ans) ans = cur_up - cur_down;
		// update minimum prefix summery
		if (cur_down > summery + arr[x].down)
			cur_down = summery + arr[x].down, cur_up = summery + arr[x].down;
		// update prefix summery
		summery += arr[x].sum;
	}
	printf("%lli", ans);
	return static_cast<int>(0b00ll);
}
