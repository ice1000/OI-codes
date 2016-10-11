#include <stdio.h>

int main(int argc, char *argv[]) {
    int a, i;
    scanf("%i", &a);
    for (i = 2; i * i <= a; ++i) {
        if (!(a % i)) {
            printf("No");
            break;
        }
    }
    if (i * i > a) printf("Yes");
    return 0;
}


