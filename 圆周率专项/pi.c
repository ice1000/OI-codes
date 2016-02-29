#include <stdio.h>
#include <math.h>

int main(int argc, char** argv){
  FILE* fp = fopen("./res.pi", "w+" );
  float pi=2;
  int  i;
  for(i=100;i>=1;i--){
      pi=pi*(float)i/(2*i+1)+2;
   }
   fprintf(fp, "%f",pi);
}