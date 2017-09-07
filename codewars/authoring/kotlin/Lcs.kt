fun lcs(a: String, b: String): String {
	if ("" == a || "" == b) return ""
	val m = Array(a.length) { IntArray(b.length) }
	for (i in 0 until a.length) {
		for (j in 0 until b.length) {
			if (a[i] == b[j]) m[i][j] = if (i != 0 && j != 0) m[i - 1][j - 1] + 1 else 1
			else
				m[i][j] = if (i != 0 && j != 0) Math.max(m[i][j - 1], m[i - 1][j]) else if (i != 0) m[i - 1][j] else if (j != 0) m[i][j - 1] else 0
		}
	}
	val r = StringBuilder()
	var i = a.length - 1
	var j = b.length - 1
	while (i >= 0 && j >= 0) {
		if (a[i] == b[j]) {
			r.insert(0, a[i])
			i--
			j--
		} else {
			val x = if (i != 0) m[i - 1][j] else 0
			val y = if (j != 0) m[i][j - 1] else 0
			if (x < y) j-- else i--
		}
	}
	return r.toString()
}
