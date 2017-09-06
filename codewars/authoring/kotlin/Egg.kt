import java.math.BigInteger

import java.math.BigInteger.ZERO
import java.math.BigInteger.valueOf

fun height(n: BigInteger, m: BigInteger): BigInteger {
	var n = n
	if (n == ZERO || m == ZERO) return ZERO
	if (n > m) n = m
	var c = valueOf(1)
	var b = valueOf(1)
	var a = valueOf(0)
	while (c <= n) {
		val d = (m + valueOf(1) - c) * b / c
		c += valueOf(1)
		b = d
		a = a.add(d)
	}
	return a
}
