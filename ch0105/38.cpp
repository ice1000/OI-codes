#include<stdio.h>

int main(int argc,char** argv){
//	FILE* fp = fopen("Fuck.exe","w+");
////	int i;
//	for(;;){
//		fprintf(fp,"Hey,Fuck you!!!\n");
//	}
	int i,j;
	scanf("%d",&i);
	for(j = 2; j < i/2; j++ ){
		if(i%j == 0){
			printf("%d",i/j);
			break;
		}
	}
	return 0;
}