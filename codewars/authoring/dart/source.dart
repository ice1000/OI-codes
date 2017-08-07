int height(int n, int m) {
  if (n == 0 || m == 0) return 0;
  if (n > m) n = m;
  int c = 1;
  int b = 1;
  int a = 0;
  while (c <= n) {
    int d = (m + 1 - c) * b ~/ c;
    c++;
    b = d;
    a += d;
  }
  return a;
}

