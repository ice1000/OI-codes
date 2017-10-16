private var p = 1e9.toInt().toLong()

/**
 * set true to enable debug
 */
internal var debug = false

private fun log2(x: Long): Int {
	var x = x
	var ans = 0
	while (true) {
		x = x shr 1
		if (x == 0L) break
		ans++
	}
	return ans
}

private fun mul(x: Long, y: Long, z: Long): Long {
	var x = x
	var y = y
	if (z == 2L) {
		when {
			x and 1 != 0L -> y = y shr 1
			y and 1 != 0L -> x = x shr 1
			else -> throw RuntimeException("shit")
		}
	}
	return x % p * (y % p) % p
}

private fun sumTimes(first: Long, n: Long, k: Long, t: Long): Long {
	var first = first
	var n = n
	first -= k
	if (first < 1) {
		n -= 1 - first
		first = 1
	}
	return if (n <= 0) 0 else mul(mul(first + first + n - 1, n, 2L), t, 1)
}

internal fun elderAge(n: Long, m: Long, k: Long, newp: Long): Long {
	var n = n
	var m = m
	var k = k
	if (n == 0L || m == 0L) return 0
	if (k < 0) k = 0
	if (n < m) {
		val tmp = n
		n = m
		m = tmp
	}
	p = newp
	if (n == m && n and -n == n) return sumTimes(1, n - 1, k, m)
	val N = log2(n)
	val M = log2(m)
	val centerWidth = 1L shl N
	val centerHeight = 1L shl M
	if (N == M) {
		val rightWidth = n - centerWidth
		val bottomHeight = m - centerHeight
		val bottomSum = sumTimes(centerHeight, centerWidth, k, bottomHeight)
		return ((sumTimes(centerWidth, centerHeight, k, rightWidth) + bottomSum) % p + (elderAge(rightWidth, bottomHeight, k, p) + elderAge(centerWidth, centerHeight, k, p)) % p) % p
	} else {
		val leftWidth = 1L shl N
		val leftSum = sumTimes(0, leftWidth, k, m)
		var rightSum = elderAge(n - leftWidth, m, k - leftWidth, p)
		if (leftWidth > k) {
			rightSum += mul(mul(leftWidth - k, m, 1), n - leftWidth, 1)
			rightSum %= p
		}
		return (leftSum + rightSum) % p
	}
}
