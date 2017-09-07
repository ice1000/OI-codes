import org.junit.Test

import java.util.Arrays
import java.util.Random

import org.junit.Assert.*

class LcsTest {

	@Test
	fun fixedTests() {
		assertEquals("", lcs("", ""))
		assertEquals("", lcs("abc", ""))
		assertEquals("", lcs("", "abc"))
		assertEquals("", lcs("a", "b"))
		assertEquals("a", lcs("a", "a"))
		assertEquals("ac", lcs("abc", "ac"))
		assertEquals("abc", lcs("abcdef", "abc"))
		assertEquals("acf", lcs("abcdef", "acf"))
		assertEquals("nottest", lcs("anothertest", "notatest"))
		assertEquals("12356", lcs("132535365", "123456789"))
		assertEquals("final", lcs("nothardlythefinaltest", "zzzfinallyzzz"))
		assertEquals("acdefghijklmnoq", lcs("abcdefghijklmnopq", "apcdefghijklmnobq"))
	}

	@Test
	fun intermediateRandomTest() {
		for (i in 0..71) test(randomString(20), randomString(20))
	}

	@Test
	fun hardRandomTest() {
		for (i in 0..23) test(randomString(400), randomString(400))
	}

	@Test
	fun extremeRandomTest() {
		for (i in 0..11) test(randomString(6000), randomString(6000))
	}

	companion object {
		private val r = Random(System.currentTimeMillis())

		private fun randomString(len: Int): String {
			val i = IntArray(len)
			Arrays.setAll(i) { r.nextInt(26) + 97 }
			val ret = CharArray(len)
			for (j in i.indices) ret[j] = i[j].toChar()
			return String(ret)
		}

		private fun sol(a: String, b: String): String {
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

		private fun isSubsequenceOf(sub: String, full: String): Boolean {
			return "" == sub || "" != full && if (sub[0] == full[0])
				isSubsequenceOf(sub.substring(1), full.substring(1))
			else
				isSubsequenceOf(sub, full.substring(1))
		}

		private fun test(a: String, b: String) {
			val res = lcs(a, b)
			assertTrue(isSubsequenceOf(res, a))
			assertTrue(isSubsequenceOf(res, b))
			assertEquals(sol(a, b).length.toLong(), res.length.toLong())
		}
	}
}