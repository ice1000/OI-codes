#include<stdio.h>

int main(int argc, char* argv[]){
    int last = 1;
    int next = 1;
    int cnt;
    scanf("%i", &cnt);
    if(cnt == 1 || cnt == 2){
        printf("1");
        return 0;
    }
    cnt--;
    cnt--;
    while(cnt--){
        int i = next;
        next += last;
        last = i; 
    }
    printf("%i", next);
    // while(1);
    return 0;
}
