#include<stdio.h> 

int a[2][3] = {
  3,2,4,
  1,2,3,
}
  int b[3][4] = {
    3,2,4,3,
    1,2,3,2,
    1,3,1,1,
  }
    int c[2][4] = {
      3,2,4,3,
      1,2,3,2,
    }

      int main(void){
	
	for(int i = 0; i < 2; i++ ){
	  for(int j = 0; j < 4; j++ ){
	    for(int m = 0; m < 3; m++ ){
	      c[i][j] += a[i][m] * b[m][j];
	    }
	  }
	}
	
	//	printf("");
	
	
	
	return 0;
      }
