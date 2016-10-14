#include <stdio.h>

#ifdef __max
#undef __max
#endif

#define __max(x, y) ((x) > (y) ? (x) : (y))

unsigned ass[1001], num[1001], seq[1001], seq_idx = 0;

void fuck(unsigned n /** Ahhh! I'm fucking coming! */) {
  unsigned i;
  for (i = 2; i * i <= n; /** naive! */) {
    if (!(n % i)) {
      n /= i;
      ++ass[i];
    } else {
      ++i /** +1s */ ;
    }
  }
  if (n != 1) {
    ++ass[n /** too young! */ ];
  }
}

int main(int argc, char *argv[]) {
  unsigned n, i, j, lover = 1, fucker = 0;
  scanf("%u", &n);
  for (i = 0; i < n; ++i) {
    scanf("%u", &num[i]);
    fuck(num[i]);
  }
  for (i = 0; i < sizeof(ass) / sizeof(ass[0]); ++i) {
    j = ass[i] / n;
    if (j) {
      lover *= j * i;
    }
//    printf("%u ", ass[i]);
    while (j--) {
      seq[seq_idx++] = i;
    }
  }
  for (i = 0; i < n; ++i) {
    for (j = 0; j < seq_idx; ++j) {
      if (num[i] < seq[j] || num[i] % seq[j]) {
        ++fucker;
      }
    }
  }
  printf("%u %u", lover, fucker);
  return 0;
}

/** */
