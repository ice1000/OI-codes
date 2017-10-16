import org.junit.AfterClass
import org.junit.BeforeClass
import org.junit.Test

import org.junit.Assert.assertEquals
import org.junit.Assert.fail

class ImmortalTest {

	@Test
	fun example() {
		assertEquals(5, elderAge(8, 5, 1, 100))
		assertEquals(224, elderAge(8, 8, 0, 100007))
		assertEquals(11925, elderAge(25, 31, 0, 100007))
		assertEquals(4323, elderAge(5, 45, 3, 1000007))
		assertEquals(1586, elderAge(31, 39, 7, 2345))
		assertEquals(808451, elderAge(545, 435, 342, 1000007))
		// You need to run this test very quickly before attempting the actual tests :)
		assertEquals(5456283, elderAge(28827050410L, 35165045587L, 7109602, 13719506))
	}

	@Test
	fun theElderIsInterested() {
		println("<p><font color=\"green\">100 test cases\\nm,n: 2^5 - 2^10\\nl: 0 - 19\\nt: 2^5 - 2^15</font></p>")
		println("Young man, you should learn a thing or two...")
		for (i in 0..99) {
			val m = Math.floor(Math.pow(2.0, Math.random() * 5 + 5)).toLong()
			val n = Math.floor(Math.pow(2.0, Math.random() * 5 + 5)).toLong()
			val l = (Math.random() * 20).toLong()
			val t = Math.floor(Math.pow(2.0, Math.random() * 10 + 5)).toLong()
			val expected = Immortal2.elderAge(m, n, l, t)
			val actual = elderAge(m, n, l, t)
			if (expected != actual) {
				good = false
				if (debug)
					println("The Elder says: \\n<p><font color=\"yellow\">m=$m, n=$n, l=$l, t=$t</font></p>")
			} else
				passed++
			assertEquals(expected, actual)
		}
	}

	@Test
	fun theElderIsExcited() {
		println("<p><font color=\"yellow\">300 test cases\\nm,n: 2^8 - 2^20\\nl: 0 - 9999\\nt: 2^10 - 2^20</font></p>")
		println("You're too young and too simple!")
		for (i in 0..299) {
			val m = Math.floor(Math.pow(2.0, Math.random() * 12 + 8)).toLong()
			val n = Math.floor(Math.pow(2.0, Math.random() * 12 + 8)).toLong()
			val l = (Math.random() * 10000).toLong()
			val t = Math.floor(Math.pow(2.0, Math.random() * 10 + 10)).toLong()
			val expected = Immortal2.elderAge(m, n, l, t)
			val actual = elderAge(m, n, l, t)
			if (expected != actual) {
				good = false
				if (debug)
					println("The Elder says: \\n<p><font color=\"yellow\">m=$m, n=$n, l=$l, t=$t</font></p>")
			} else
				passed++
			assertEquals(expected, actual)
		}
	}

	@Test
	fun theElderIsAngry() {
		println("<p><font color=\"red\">500 test cases\\nm,n: 2^32 - 2^48\\nl: 0 - 9999999\\nt: 2^16 - 2^26</font></p>")
		println("And sometimes naive!")
		for (i in 0..499) {
			val m = Math.floor(Math.pow(2.0, Math.random() * 16 + 32)).toLong()
			val n = Math.floor(Math.pow(2.0, Math.random() * 16 + 32)).toLong()
			val l = (Math.random() * 1e7).toLong()
			val t = Math.floor(Math.pow(2.0, Math.random() * 10 + 16)).toLong()
			val expected = Immortal2.elderAge(m, n, l, t)
			val actual = elderAge(m, n, l, t)
			if (expected != actual) {
				good = false
				if (debug)
					println("The Elder says: \\n<p><font color=\"yellow\">m=$m, n=$n, l=$l, t=$t</font></p>")
			} else
				passed++
			assertEquals(expected, actual)
		}
	}

	private object Immortal2 {
		private var p = 1e9.toInt().toLong()

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
				if (x and 1 != 0L)
					y = y shr 1
				else if (y and 1 != 0L)
					x = x shr 1
				else
					throw RuntimeException("shit")
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
			return if (N == M) {
				val rightWidth = n - centerWidth
				val bottomHeight = m - centerHeight
				val bottomSum = sumTimes(centerHeight, centerWidth, k, bottomHeight)
				((sumTimes(centerWidth, centerHeight, k, rightWidth) + bottomSum) % p + (elderAge(rightWidth, bottomHeight, k, p) + elderAge(centerWidth, centerHeight, k, p)) % p) % p
			} else {
				val leftWidth = 1L shl N
				val leftSum = sumTimes(0, leftWidth, k, m)
				var rightSum = elderAge(n - leftWidth, m, k - leftWidth, p)
				if (leftWidth > k) {
					rightSum += mul(mul(leftWidth - k, m, 1), n - leftWidth, 1)
					rightSum %= p
				}
				(leftSum + rightSum) % p
			}
		}
	}

	companion object {
		private var date: Long = 0
		private var passed: Long = 0
		private var good = true

		@BeforeClass
		@JvmStatic
		fun init() {
			date = System.currentTimeMillis()
		}

		@AfterClass
		@JvmStatic
		fun end() {
			val end = System.currentTimeMillis()
			val timeDiff = (date - end) / 1000
			if (passed >= 900) {
				println("You spent.. " + timeDiff + "ms")
				if (timeDiff <= 1)
					println("You finished all the tests within 1 second. The Elder is very happy! +1s")
				else
					println("The Elder is pleased!")
			} else {
				println("The Elder is displeased!")
				fail()
			}
		}
	}

}