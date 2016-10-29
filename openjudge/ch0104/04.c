#include <stdio.h>

int main(int argc, const char *argv[]) {
  puts(getchar() & 1 ? "YES" : "NO");
  return 0;
}
