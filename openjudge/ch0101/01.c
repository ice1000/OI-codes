#include <stdio.h>

int main() {
  int i = 3;
  switch(i) {
  case 1 ... 5:
    printf("Hello, World!");
    break;
  case 6 ... 10:
    break;
  }
  return 0;
}

