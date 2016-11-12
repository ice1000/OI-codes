#include <stdio.h>
#include <string.h>
#include <windows.h>

#define init(x, y) (memset(x, y, sizeof(x)))
#define true 1
#define false 0

typedef unsigned long long number;

number n, m, k, ans;
int map[10];

int judge(number num) {
	init(map, 0);
	number i = 1, j = 1;
	while (num / i) {
		if (map[(num / i) % 10]) return false;
		++map[(num / i) % 10];
		if (i >= k) {
			--map[(num / j) % 10];
			j *= 10;
		}
		i *= 10;
	}
	return true;
}

DWORD WINAPI threadProc1() {
	number i;
	for (i = n; i <= n + m / 10; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc2() {
	number i;
	for (i = n + m / 10 + 1; i <= n + m / 10 * 2; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc3() {
	number i;
	for (i = n + m / 10 * 2 + 1; i <= n + m / 10 * 3; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc4() {
	number i;
	for (i = n + m / 10 * 3 + 1; i <= n + m / 10 * 4; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc5() {
	number i;
	for (i = n + m / 10 * 4 + 1; i <= n + m / 10 * 5; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc6() {
	number i;
	for (i = n + m / 10 * 5 + 1; i <= n + m / 10 * 6; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc7() {
	number i;
	for (i = n + m / 10 * 6 + 1; i <= n + m / 10 * 7; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc8() {
	number i;
	for (i = n + m / 10 * 7 + 1; i <= n + m / 10 * 8; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc9() {
	number i;
	for (i = n + m / 10 * 8 + 1; i <= n + m / 10 * 9; ++i) if (judge(i)) ++ans;
	return 0;
}

DWORD WINAPI threadProc0() {
	number i;
	for (i = n + m / 10 * 9 + 1; i <= n + m; ++i) if (judge(i)) ++ans;
	return 0;
}

int main(int argc, const char *argv[]) {
//	freopen("num.in", "r", stdin);
//	freopen("num.out", "w", stdout);
	scanf("%llu %llu %llu", &n, &m, &k);
	m -= n;
	for (auto thread : {
			threadProc1, threadProc2, threadProc3,
			threadProc4, threadProc5, threadProc6,
			threadProc7, threadProc8, threadProc9, threadProc0})
		CreateThread(NULL, 0xffff, (LPTHREAD_START_ROUTINE) thread, NULL, 0, NULL);
	Sleep(500);
	printf("%llu", ans);
	return 0;
}
