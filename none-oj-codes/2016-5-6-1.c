#include <stdio.h>
// #include <memory.h>
const int size = 0xfff;
/*typedef struct {
    // score 
    int a;
    // from l 2 r, increase x;
//    int l, r, x; 
} per ;*/
inline void nextInt(int& a) {
    a = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9' )
        ch = getchar();
    while (ch >= '0' && ch <= '9' ) {
        a = a * 10 + ch - '0' ;
        ch = getchar();
    }
}
int main(int argc, char* argv[]){
    long n, i, j, q, min = size, max = -size;
    int a[size];
    scanf("%ld", &n);
    for(i = 0; i < n; i++) {
        scanf("%ld", &a[i]);
//        if(a[i] > max) max = a[i];
//        if(a[i] < min) min = a[i];
    }
    scanf("%ld", &q);
    for(i = 0; i < q; i++) {
        int l, r, x;
        nextInt(l);
        nextInt(r);
        scanf("%d", &x);
        for(j = l - 1; j < r && j < n; j++) a[j] += x;
    }
    for(i = 0; i < n; i++) {
        if(a[i] > max) max = a[i];
        if(a[i] < min) min = a[i];
    }
    printf("%ld %ld\n", max, min);
    return 0;
}
/*
6
144 137 89 126 135 98
6
1 3 4
2 5 -2
3 3 1
3 4 2
3 5 3
1 6 5
*/
