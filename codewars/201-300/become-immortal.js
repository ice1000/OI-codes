lowbit = (x) => x & -x;

function log2(x) {
    var ans = 0;
    while (x >>= 1) ans++;
    return ans;
}

function mul(x, y, z, p) {
    if (z == 2) {
        if (x & 1) y >>= 1;
        else if (y & 1) x >>= 1;
        else throw "";
    }
    return (x % p) * (y % p) % p;
}

function sumTimes(first, n, k, t, p) {
    first -= k;
    if (first < 1) n -= (1 - first), first = 1;
    if (n <= 0) return 0;
    return mul(mul(first + (first + n - 1), n, 2, p), t, 1, p);
}

function solve(n, m, k, p) {
    if (n == 0 || m == 0) return 0;

    if (k < 0) k = 0;
    if (n < m) {
				var temp = n;
				n = m;
				m = temp;
		}

    if (n == m && lowbit(n) == n) {
        return sumTimes(1, n - 1, k, m);
    }

    var N = log2(n);
		var M = log2(m);
    var centerWidth = (1 << N), centerHeight = (1 << M);
    if (N == M) {
        var rightWidth = n - centerWidth, rightHeight = centerHeight;
        var bottomWidth = centerWidth, bottomHeight = m - centerHeight;

        var rightSum = sumTimes(centerWidth, rightHeight, k, rightWidth, p);
        var bottomSum = sumTimes(centerHeight, bottomWidth, k, bottomHeight, p);

        var sideSum = solve(rightWidth, bottomHeight, k, p);
        var centerSum = solve(bottomWidth, rightHeight, k, p);
        return ((rightSum + bottomSum) % p + (sideSum + centerSum) % p) % p;
    } else {

        var leftWidth = (1 << N), leftHeight = m;
        var rightWidth = n - leftWidth, rightHeight = leftHeight;
        var leftSum = sumTimes(0, leftWidth, k, leftHeight, p);
        var rightSum = solve(rightWidth, rightHeight, k - leftWidth, p);

        if (leftWidth > k) {
            rightSum += mul(mul(leftWidth - k, m, 1, p), n - leftWidth, 1, p);
            rightSum %= p;
        }
        return (leftSum + rightSum) % p;
    }
}

function elderAge(m, n, l, t) {
		return solve(n, m, l, t);
}

