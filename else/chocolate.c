#include <stdio.h>

int n, k, a[100001], min = 0xFFF;

void init() {
	freopen("chocolate.in", "r", stdin);
	freopen("chocolate.out", "w+", stdout);
}

typedef struct {
	int ret;
	int max;
} pair ;

pair check(int m) {
	int i, j = 0, t = 0, max = 0, end = 0;
	for(i = 0; i < n; i++) {
		t += a[i];
		if(t >= m) {
			max = max > t ? max : t;
			if(!end) t = 0;
			j++;
		}
		if(j >= k) end = 1;
//		printf("m = %d, max = %d, t = %d\n", m, max, t);
	}
	pair p;
	p.max = max;
	p.ret = j > k ? 1 : j == k ? 0 : -1;
//	printf("j = %d, k = %d, p.ret = %d\n", j, k, p.ret);
	return p;
}

void find(int l, int r) {
	if(l > r) return ;
	int mid = (l + r + 1) / 2;
	pair res = check(mid);
	switch(res.ret) {
		case 0:
			min = res.max;
			break;
		case 1:
			min = res.max;
			find(l, mid - 1);
			break;
		case -1:
			find(mid + 1, r);
			break;
	}
}

int main(int argc, char* argv[]) {
	init();
	int i, j;
	scanf("%d%d", &n, &k);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	// 最小的理想情况是所有人均分
	// 最多的情况是所有人只拿1，剩下的全部给另一个人
	find(n / k + 1, n - k + 1);
	printf("%d", min);
	return 0;
}
