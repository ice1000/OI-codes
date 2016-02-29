#include <stdio.h>
// this doesn't work
int main(int argc, char** argv){
	double pi = 3.0;
	int i = 0;
	for(i = 1; i < 100000; i++){
		pi += 1 /(2 * i - 1);
		pi -= 1 /(2 * i);
    }
    printf("pi = %lf\n", pi);
	return 0;
}
