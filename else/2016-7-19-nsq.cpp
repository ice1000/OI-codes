#include <stdio.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	freopen("nsq.in", "r", stdin );
	freopen("nsq.out","w+",stdout);
	long long i, n, p, a[100010];
	scanf("%I64d %I64d", &n, &p);
	double av = 0, tt = 1.0 / n;
	for(i = 0; i < n; i++) {
		scanf("%I64d", &a[i]);
		tt *= a[i];
	}
	for(i = 0; i < n; i++) {
		av += (tt * 1.0 / a[i]);
		if(av > p) av -= p;
	}
	printf("%.10lf", av);
	return 0;
}
