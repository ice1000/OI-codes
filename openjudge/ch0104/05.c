#include <stdio.h>

int main() {
  long long i, j;
  scanf("%lli %lli", &i, &j);
  puts(i != j ? i < j ? "<" : ">" : "=");
  return 0;
}
