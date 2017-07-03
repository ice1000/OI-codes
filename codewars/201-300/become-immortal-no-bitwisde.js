is_2 = (x) => {
		while (!(x & 1)) x = Math.floor(x / 2);
		return x == 1;
}

fastCore = (a, b, m) => {
		var s = a + b;
		if (s >= a && s >= b) return s % m;
		if (a >= m && a > m - b) return fastCore(a - m, b, m);
		if (b >= m && b > m - a) return fastCore(a, b - m, m);
		return s;
}

fastPlus = (a, b, m) => {
		var ret = 0;
		a %= m, b %= m;
		while (b) {
				if(b & 1) ret = fastCore(ret, a, m);
				b = Math.floor(b / 2);
				a = fastCore(a, a, m);
		}
		return ret;
}

log2 = (x) => {
    var ans = 0;
    while (x = Math.floor(x / 2)) ans++;
    return ans;
}

mul = (x, y, z, p) => {
    if (z == 2) {
        if (x & 1) y = Math.floor(y / 2);
        else if (y & 1) x = Math.floor(x / 2);
        else throw "";
    }
    return fastPlus(x, y, p);
}

sumTimes = (first, n, k, t, p) => {
    first -= k;
    if (first < 1) n -= (1 - first), first = 1;
    if (n <= 0) return 0;
    var fst = first + first + n - 1;
    return mul(mul(fst, n, 2, p), t, 1, p);
}

solve = (n, m, k, p) => {
    if (n == 0 || m == 0) return 0;

    if (k < 0) k = 0;
    if (n < m) {
        var temp = n;
        n = m;
        m = temp;
    }

    if (n == m && is_2(n)) return sumTimes(1, n - 1, k, m, p);

    var N = log2(n);
    var M = log2(m);
    var centerWidth = Math.pow(2, N);
    var centerHeight = Math.pow(2, M);
    if (N == M) {
        var rightWidth = n - centerWidth;
        var rightHeight = centerHeight;
        var bottomWidth = centerWidth;
        var bottomHeight = m - centerHeight;

        var rightSum = sumTimes(centerWidth, rightHeight, k, rightWidth, p);
        var bottomSum = sumTimes(centerHeight, bottomWidth, k, bottomHeight, p);

        var sideSum = solve(rightWidth, bottomHeight, k, p);
        var centerSum = solve(bottomWidth, rightHeight, k, p);

        return fastCore(fastCore(fastCore(rightSum, bottomSum, p), sideSum, p), centerSum, p);
    } else {
        var leftWidth = Math.pow(2, N);
        var leftHeight = m;
        var rightWidth = n - leftWidth;
        var rightHeight = leftHeight;
        var leftSum = sumTimes(0, leftWidth, k, leftHeight, p);
        var rightSum = solve(rightWidth, rightHeight, k - leftWidth, p);

        if (leftWidth > k) {
						var inter = mul(mul(leftWidth - k, m, 1, p), n - leftWidth, 1, p);
						rightSum = fastCore(rightSum, inter, p);
				}
        return fastCore(leftSum, rightSum, p);
    }
}

// debug = true;

elderAge = solve;

