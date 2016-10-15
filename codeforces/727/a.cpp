#include <stdio.h>

#define int long long

int seq[1000001], end = -1, a, target;

int dfs(int idx) {
  if (seq[idx] == target) {
    end = idx;
    return 1;
  }
  if (seq[idx] > target) return 0;
  int i = seq[idx++];
  seq[idx] = i << 1;
  if (dfs(idx)) return 1;
  seq[idx] = i * 10 + 1;
  if (dfs(idx)) return 1;
}

#undef int
int main(int argc, char *argv[]) {
#define int long long
  
  int i, j;
  scanf("%i %i", &seq[0], &target);
  if (!dfs(0)) {
    printf("NO");
  } else {
    printf("YES\n%lli\n", end + 1);
    for (i = 0; i <= end; ++i) {
      printf("%lli ", seq[i]);
    }
  }
  return 0;
}
