package codewars;

import org.junit.Test;

import java.util.Random;
import java.io.File;
import java.nio.file.Files;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.fail;
import static codewars.FastPower.pow;
import static org.junit.Assert.assertEquals;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class FastPowerTest {
		private static Random random = new Random(System.currentTimeMillis());

		@Test
		public void smallRandomTests() {
				int i = 10;
				while (i-- > 0) {
						long a = Math.abs(random.nextInt(10)) + 1;
						long b = Math.abs(random.nextInt(10)) + 1;
						long m = Math.abs(random.nextInt(10)) + 1;
						assertEquals(Math.pow(a, b) % m, pow(a, b, m), 1e-2);
				}
		}

		@Test(timeout = 10000)
		public void bigRandomTests() {
				int i = 4000;
				while (i-- > 0) {
						long a = gen();
						long b = gen();
						long m = gen() >>> 1;
						if (FastPower.DEBUG) System.out.println("<p><font color=\"green\">a = " + a + ", b = " + b + ", m = " + m + "</font></p>");
						assertEquals(pow_(a, b, m), pow(a, b, m));
				}
		}

		private static long gen() {
				long a = random.nextLong();
				final long half = Long.MAX_VALUE >>> 1;
				while (a < half) a += half;
				return Math.abs(a);
		}

		private static long plus_(long a, long b, long m) {
				long s = a + b;
				if (s >= a && s >= b) return s % m;
				if (a > m) return plus_(a % m, b, m);
				if (b > m) return plus_(a, b % m, m);
				return a - m + b;
		}

		private static long mul_(long a, long b, long m) {
				long ret = 0;
				while (b != 0) {
						if ((b & 1) != 0) ret = plus_(ret, a, m);
						b >>>= 1;
						a = plus_(a, a, m);
				}
				return ret;
		}

		@Test
		public void notUsingThrow() throws Exception {
				Files.lines(new File("/home/codewarrior/solution.txt").toPath()).forEach(str -> {
								assertFalse(str.contains("Integer"));
								assertFalse(str.contains("Big"));
								assertFalse(str.contains("char"));
								assertFalse(str.contains("byte"));
								assertFalse(str.contains("math"));
								assertFalse(str.contains("\""));
								assertFalse(str.contains("\'"));
								assertFalse(str.contains("\\u"));
						});
		}

		private static long pow_(long a, long b, long m) {
				long ret = 1;
				while (b != 0) {
						if ((b & 1) != 0) ret = mul_(ret, a, m);
						b >>>= 1;
						a = mul_(a, a, m);
				}
				return ret;
		}

}
