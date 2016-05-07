#include <stdio.h>
#include <iostream>
long long A, M, a = 1;
void change() { a *= A; a %= M; }
int main(int argc, char* argv[]) {
    long long N;
    scanf("%lld%lld%lld", &A, &N, &M);
//    std::cin>>A>>N>>M;
    A %= M;
    while(N--)
        change();
//    std::cout<<a<<" ";
    printf("%lld ", a);
    change();
//    std::cout<<a<<std::endl;
    printf("%lld",  a);
    return 0;
}
