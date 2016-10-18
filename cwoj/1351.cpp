#include <stdio.h>
#include <math.h>
//#include <iostream>

long long gcd(long long a, long long b) {
  return !b ? a : gcd(b, a % b);
}

int main(int argc, char *argv[]) {
  long long n, a1, a2, a3, i, j, k;
  scanf("%lli %lli %lli %lli", &n, &a1, &a2, &a3);
//  std::cin>>n>>a1>>a2>>a3;
  i = a1 * a2 / gcd(a1, a2);
  j = a3 * a2 / gcd(a3, a2);
  k = a1 * a3 / gcd(a1, a3);
  printf("%lli",
      n - n / a1 - n / a2 - n / a3 + n / i + n / j + n / k
      - n / (i * a3 / gcd(i, a3))
  );
  return 0;
}

/*
2015
4 5 6

12
2 3 6
2 4 6 8 10 12
3 6 9 12
6 12
2 3 4 6 8 9 10 12
*/

