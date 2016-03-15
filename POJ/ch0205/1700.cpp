#include<stdio.h>
#include<stdlib.h>
#include<queue>
using namespace std;

const int SIZE = 1000;
int cnt = 0;

int step[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

int main(int argc,char** argv){
  while(1){
    cnt++;
    printf("No. %i\n", cnt);
  }
  system("PAUSE");
  return 0;
}
