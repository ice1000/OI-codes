import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

public class ImmortalTest {
	private static long date;
	private static long passed = 0;
	private static boolean good = true;

	@BeforeClass
	public static void init() {
		date = System.currentTimeMillis();
	}

	@Test
	public void example() {
		assertEquals(5, Immortal.elderAge(8, 5, 1, 100));
		assertEquals(224, Immortal.elderAge(8, 8, 0, 100007));
		assertEquals(11925, Immortal.elderAge(25, 31, 0, 100007));
		assertEquals(4323, Immortal.elderAge(5, 45, 3, 1000007));
		assertEquals(1586, Immortal.elderAge(31, 39, 7, 2345));
		assertEquals(808451, Immortal.elderAge(545, 435, 342, 1000007));
		// You need to run this test very quickly before attempting the actual tests :)
		assertEquals(5456283, Immortal.elderAge(28827050410L, 35165045587L, 7109602, 13719506));
	}

	@Test
	public void theElderIsInterested() {
		System.out.println("<p><font color=\"green\">100 test cases\\nm,n: 2^5 - 2^10\\nl: 0 - 19\\nt: 2^5 - 2^15</font></p>");
		System.out.println("Young man, you should learn a thing or two...");
		for (int i = 0; i < 100; i++) {
			long m = (long) Math.floor(Math.pow(2, Math.random() * 5 + 5)),
					n = (long) Math.floor(Math.pow(2, Math.random() * 5 + 5)),
					l = (long) (Math.random() * 20),
					t = (long) Math.floor(Math.pow(2, Math.random() * 10 + 5));
			long expected = Immortal2.elderAge(m, n, l, t), actual = Immortal.elderAge(m, n, l, t);
			if (expected != actual) {
				good = false;
				if (Immortal.debug)
					System.out.println("The Elder says: \\n<p><font color=\"yellow\">m=" + m + ", n=" + n + ", l=" + l + ", t=" + t + "</font></p>");
			} else passed++;
			assertEquals(expected, actual);
		}
	}

	@Test
	public void theElderIsExcited() {
		System.out.println("<p><font color=\"yellow\">300 test cases\\nm,n: 2^8 - 2^20\\nl: 0 - 9999\\nt: 2^10 - 2^20</font></p>");
		System.out.println("You're too young and too simple!");
		for (int i = 0; i < 300; i++) {
			long m = (long) Math.floor(Math.pow(2, Math.random() * 12 + 8)),
					n = (long) Math.floor(Math.pow(2, Math.random() * 12 + 8)),
					l = (long) (Math.random() * 10000),
					t = (long) Math.floor(Math.pow(2, Math.random() * 10 + 10));
			long expected = Immortal2.elderAge(m, n, l, t), actual = Immortal.elderAge(m, n, l, t);
			if (expected != actual) {
				good = false;
				if (Immortal.debug)
					System.out.println("The Elder says: \\n<p><font color=\"yellow\">m=" + m + ", n=" + n + ", l=" + l + ", t=" + t + "</font></p>");
			} else passed++;
			assertEquals(expected, actual);
		}
	}

	@Test
	public void theElderIsAngry() {
		System.out.println("<p><font color=\"red\">500 test cases\\nm,n: 2^32 - 2^48\\nl: 0 - 9999999\\nt: 2^16 - 2^26</font></p>");
		System.out.println("And sometimes naive!");
		for (int i = 0; i < 500; i++) {
			long m = (long) Math.floor(Math.pow(2, Math.random() * 16 + 32)),
					n = (long) Math.floor(Math.pow(2, Math.random() * 16 + 32)),
					l = (long) (Math.random() * 1e7),
					t = (long) Math.floor(Math.pow(2, Math.random() * 10 + 16));
			long expected = Immortal2.elderAge(m, n, l, t), actual = Immortal.elderAge(m, n, l, t);
			if (expected != actual) {
				good = false;
				if (Immortal.debug)
					System.out.println("The Elder says: \\n<p><font color=\"yellow\">m=" + m + ", n=" + n + ", l=" + l + ", t=" + t + "</font></p>");
			} else passed++;
			assertEquals(expected, actual);
		}
	}

	@AfterClass
	public static void end() {
		long end = System.currentTimeMillis();
		long timeDiff = (date - end) / 1000;
		if (passed >= 900) {
			System.out.println("You spent.. " + timeDiff + "ms");
			if (timeDiff <= 1) System.out.println("You finished all the tests within 1 second. The Elder is very happy! +1s");
			else System.out.println("The Elder is pleased!");
		} else {
			System.out.println("The Elder is displeased!");
			fail();
		}
	}

	private static class Immortal2 {
		private static long p = (int) 1e9;

		private static int log2(long x) {
			int ans = 0;
			while ((x >>= 1) != 0) ans++;
			return ans;
		}

		private static long mul(long x, long y, long z) {
			if (z == 2) {
				if ((x & 1) != 0) y >>= 1;
				else if ((y & 1) != 0) x >>= 1;
				else throw new RuntimeException("shit");
			}
			return x % p * (y % p) % p;
		}

		private static long sumTimes(long first, long n, long k, long t) {
			first -= k;
			if (first < 1) {
				n -= 1 - first;
				first = 1;
			}
			if (n <= 0) return 0;
			return mul(mul(first + first + n - 1, n, 2L), t, 1);
		}

		static long elderAge(long n, long m, long k, long newp) {
			if (n == 0 || m == 0) return 0;
			if (k < 0) k = 0;
			if (n < m) {
				long tmp = n;
				n = m;
				m = tmp;
			}
			p = newp;
			if (n == m && (n & -n) == n) return sumTimes(1, n - 1, k, m);
			int N = log2(n), M = log2(m);
			long centerWidth = 1L << N, centerHeight = 1L << M;
			if (N == M) {
				long rightWidth = n - centerWidth, bottomHeight = m - centerHeight;
				long bottomSum = sumTimes(centerHeight, centerWidth, k, bottomHeight);
				return ((sumTimes(centerWidth, centerHeight, k, rightWidth) + bottomSum) % p + (elderAge(rightWidth, bottomHeight, k, p) + elderAge(centerWidth, centerHeight, k, p)) % p) % p;
			} else {
				long leftWidth = 1L << N;
				long leftSum = sumTimes(0, leftWidth, k, m);
				long rightSum = elderAge(n - leftWidth, m, k - leftWidth, p);
				if (leftWidth > k) {
					rightSum += mul(mul(leftWidth - k, m, 1), n - leftWidth, 1);
					rightSum %= p;
				}
				return (leftSum + rightSum) % p;
			}
		}
	}

}