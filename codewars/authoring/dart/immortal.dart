int p = 1e9.toInt();

/** set true to enable debug */
bool debug = false;

int log2(int x) {
  int ans = 0;
  while ((x >>= 1) != 0) ans++;
  return ans;
}

int mul(int x, int y, int z) {
  if (z == 2) {
    if ((x & 1) != 0)
      y >>= 1;
    else if ((y & 1) != 0)
      x >>= 1;
    else
      throw new Exception("shit");
  }
  return x % p * (y % p) % p;
}

int sumTimes(int first, int n, int k, int t) {
  first -= k;
  if (first < 1) {
    n -= 1 - first;
    first = 1;
  }
  if (n <= 0) return 0;
  return mul(mul(first + first + n - 1, n, 2), t, 1);
}

int elderAge(int n, int m, int k, int newp) {
  if (n == 0 || m == 0) return 0;
  if (k < 0) k = 0;
  if (n < m) {
    int tmp = n;
    n = m;
    m = tmp;
  }
  p = newp;
  if (n == m && (n & -n) == n) return sumTimes(1, n - 1, k, m);
  int N = log2(n), M = log2(m);
  int centerWidth = 1 << N, centerHeight = 1 << M;
  if (N == M) {
    int rightWidth = n - centerWidth, bottomHeight = m - centerHeight;
    int bottomSum = sumTimes(centerHeight, centerWidth, k, bottomHeight);
    return ((sumTimes(centerWidth, centerHeight, k, rightWidth) + bottomSum) %
                p +
            (elderAge(rightWidth, bottomHeight, k, p) +
                    elderAge(centerWidth, centerHeight, k, p)) %
                p) %
        p;
  } else {
    int leftWidth = 1 << N;
    int leftSum = sumTimes(0, leftWidth, k, m);
    int rightSum = elderAge(n - leftWidth, m, k - leftWidth, p);
    if (leftWidth > k) {
      rightSum += mul(mul(leftWidth - k, m, 1), n - leftWidth, 1);
      rightSum %= p;
    }
    return (leftSum + rightSum) % p;
  }
}
