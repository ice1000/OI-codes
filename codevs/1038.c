/*
作者:千里冰封
题目:p1038 一元三次方程求解
*/

#include <stdio.h>

double i, a, b, c, d;

double abs (double x) {
	return x > 0 ? x : -x;
}

//void find (double left, double right) {
//	if (fabs(left - right) < 0.005)
//		return;
//	double mid = (left + right) / 2;
//	if (fabs(a * mid * mid * mid + b * mid * mid + c * mid + d) < 0.01) {
//		answers[index++] = mid;
//		return;
//	}
//	if (a * mid * mid * mid + b * mid * mid + c * mid + d < 0)
//		return find(left, mid);
//	else
//		return find(mid, right);
//}

int main (int argc, char *argv[]) {
	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
	for (i = -101; i <= 101; i += 0.01)
		if (abs(a * i * i * i +
		        b * i * i +
		        c * i +
		        d) <= 0.01)
			printf("%.2lf ", i);
	return 0;
}

/*
1 -5 -4 20
*/
