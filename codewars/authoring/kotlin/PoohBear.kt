
fun interpret(e: String): String {
	return execute(IntArray(30000), 0, 0, e)
}

private fun execute(cells: IntArray, ptr: Int, clip: Int, expr: String): String {
	var ptr = ptr
	var clip = clip
	val result = StringBuilder()
	var i = 0
	while (i < expr.length) {
		when (expr[i]) {
			'+' -> cells[ptr] = normalize(cells[ptr] + 1)
			'-' -> cells[ptr] = normalize(cells[ptr] - 1)
			'>' -> ptr++
			'<' -> ptr--
			'c' -> clip = cells[ptr]
			'p' -> cells[ptr] = clip
			'T' -> cells[ptr] = normalize(cells[ptr] * 2)
			'Q' -> cells[ptr] = normalize(Math.pow(cells[ptr].toDouble(), 2.0).toInt())
			'U' -> cells[ptr] = normalize(Math.sqrt(cells[ptr].toDouble()).toInt())
			'L' -> cells[ptr] = normalize(cells[ptr] + 2)
			'I' -> cells[ptr] = normalize(cells[ptr] - 2)
			'V' -> cells[ptr] = normalize(cells[ptr] / 2)
			'A' -> cells[ptr] = normalize(cells[ptr] + clip)
			'B' -> cells[ptr] = normalize(cells[ptr] - clip)
			'Y' -> cells[ptr] = normalize(cells[ptr] * clip)
			'D' -> cells[ptr] = normalize(cells[ptr] / clip)
			'N' -> result.append(cells[ptr])
			'P' -> result.append(cells[ptr].toChar())
			'W' -> {
				val cycleEndIndex = locateCycleEndIndex(expr, i)
				while (cells[ptr] > 0) result.append(execute(cells, ptr, clip, expr.substring(i + 1, cycleEndIndex)))
				i = cycleEndIndex
			}
		}
		i++
	}
	return result.toString()
}

private fun locateCycleEndIndex(expr: String, i: Int): Int {
	var count = 1
	var j = i
	while (count > 0) {
		j++
		if (expr[j] == 'W') count++
		else if (expr[j] == 'E') count--
	}
	return j
}

private fun normalize(value: Int): Int = if (value < 0) 256 - Math.abs(value % 256) else if (value > 255) value % 256 else value

