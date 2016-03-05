/*
	s为所使用的最小的字母的序号
	t为所使用的最大的字母的序号
	w为数字的位数
*/

#include<stdio.h>

char a[26] ;
int size ;

void dfs(int idx, char n[5]){
}

int main(int argc, char** argv){
    char* ss;
    int s, t, w;
    scanf("%i%i%i", &s, &t, &w);
    scanf("%s", ss);
    size = t - s;
    s--;
    char from = s + 'a';
    for(int i = 0; i < size; i++)
        a[i] = from + i;

    printf("%s", a);
//    while(1);
    return 0;
}
