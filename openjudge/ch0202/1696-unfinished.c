#include <stdio.h>
#include <string.h>
#include <math.h>

double plus(double a, double b) {return a + b;}
double mino(double a, double b) {return a - b;}
double time(double a, double b) {return a * b;}
double devi(double a, double b) {return a / b;}

int main(int argc, char* argv[]) {
	char s[1000];
	int i, end = 0;
	int temp[1000], tidx = 0;
	memset(temp, 0, sizeof(temp[0]));
	scanf("%s", s);
	double (*cal[])(double, double) = {
		plus, mino, time, devi
	};
	for(i = 0; i < strlen(s); i++) {
		if(s[i] == ' ') {
			end = 1;
		}
		else {
			switch(s[i]) {
				case '+':
					temp[tidx++] = 0;
					break;
				case '-':
					temp[tidx++] = 1;
					break;
				case '*':
					temp[tidx++] = 2;
					break;
				case '/':
					temp[tidx++] = 3;
					break;
				default:
					break;
			}
		}
	}
	return 0;
}
