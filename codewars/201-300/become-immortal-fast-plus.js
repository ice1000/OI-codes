lowbit = (x) => x & -x;

fastCore = (a, b, m) => {
		var s = a + b;
		if (s >= a && s >= b) return s % m;
		if (a >= m && a > m - b) return fastCore(a - m, b, m);
		if (b >= m && b > m - a) return fastCore(a, b - m, m);
}

fastPlus = (a, b, m) => {
		var ret = 0;
		a %= m, b %= m;
		// if (m > 2823933639) console.log(`${a}, ${b}, ${m}`);
		while (b) {
    if(b & 1) ret = fastCore(ret, a, m);
				b = Math.floor(b / 2);
				a = fastCore(a, a, m);
		}
		// if (m > 2823933639) console.log(`${ret}\n`);
		return ret;
}

log2 = (x) => {
    var ans = 0;
    while (x >>= 1) ans++;
    return ans;
}

mul = (x, y, z, p) => {
    if (z == 2) {
        if (x & 1) y >>= 1;
        else if (y & 1) x >>= 1;
        else throw "";
    }
    return fastPlus(x, y, p);
}

sumTimes = (first, n, k, t, p) => {
    first -= k;
    if (first < 1) n -= (1 - first), first = 1;
    if (n <= 0) return 0;
    return mul(mul(fastCore(fastCore(first, first, p), n, p) - 1, n, 2, p), t, 1, p);
}

solve = (n, m, k, p) => {
    if (n == 0 || m == 0) return 0;

    if (k < 0) k = 0;
    if (n < m) {
        var temp = n;
        n = m;
        m = temp;
    }

    if (n == m && lowbit(n) == n) return sumTimes(1, n - 1, k, m, p);

    var N = log2(n);
    var M = log2(m);
    var centerWidth = 1 << N, centerHeight = 1 << M;
    if (N == M) {
        var rightWidth = n - centerWidth, rightHeight = centerHeight;
        var bottomWidth = centerWidth, bottomHeight = m - centerHeight;

        var rightSum = sumTimes(centerWidth, rightHeight, k, rightWidth, p);
        var bottomSum = sumTimes(centerHeight, bottomWidth, k, bottomHeight, p);

        var sideSum = solve(rightWidth, bottomHeight, k, p);
        var centerSum = solve(bottomWidth, rightHeight, k, p);
        return fastCore(fastCore(fastCore(rightSum, bottomSum, p), sideSum, p), centerSum, p);
    } else {
        var leftWidth = (1 << N), leftHeight = m;
        var rightWidth = n - leftWidth, rightHeight = leftHeight;
        var leftSum = sumTimes(0, leftWidth, k, leftHeight, p);
        var rightSum = solve(rightWidth, rightHeight, k - leftWidth, p);

        if (leftWidth > k)
						rightSum = fastCore(rightSum, mul(mul(leftWidth - k, m, 1, p), n - leftWidth, 1, p), p);
        return fastCore(leftSum, rightSum, p);
    }
}

function elderAge(m, n, l, t) {
		return solve(n, m, l, t);
}

