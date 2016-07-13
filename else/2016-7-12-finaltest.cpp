#include <stdio.h>

int main(int argc, char *argv[]) {
	freopen("finaltest.in", "r", stdin);
	freopen("finaltest.out", "w+", stdout);
	int m, i, score, e;
	double have = 0, money;
	// 真的猛士敢于把数组少开一位
	char name[999];
	scanf("%d", &m);
	for(i = 0; i < m; i++) {
		scanf("%s %lf %d", name, &money, &score);
		if(score >= 90)
			have += money;
	}
	scanf("%s", name);
	scanf("%i", &e);
	printf("%.2lf\n", have);
	int a = have / e;
	if(a) printf("%d", a);
	else puts("ni wei he na me diao!");
	return 0;
}
