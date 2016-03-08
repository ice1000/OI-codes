#include <stdio.h>

// 0 --> jishu; 1 --> oushu
int a[1000][2];

int main(int argc, char* argv[]){
	auto int k, i;
	a[0][0] = 1;
	a[0][1] = 8;
	scanf("%i", &k);
	for(i = 1; i < k; i++){
		a[i][1] = a[i - 1][1] * 9 + a[i - 1][0];
		a[i][0] = a[i - 1][0] * 9 + a[i - 1][1];
		a[i][1] %= 12345;
		a[i][0] %= 12345;
	}
	printf("%i", a[k - 1][1]);
	return 0;
}
