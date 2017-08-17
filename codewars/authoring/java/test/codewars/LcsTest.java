import org.junit.Test;

import java.util.Arrays;
import java.util.Random;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class LcsTest {
		private static final Random r = new Random(System.currentTimeMillis());

		private static String randomString(int len) {
				int[] i = new int[len];
				Arrays.setAll(i, n -> r.nextInt(26) + 97);
				char[] ret = new char[len];
				for (int j = 0; j < i.length; j++) ret[j] = (char) i[j];
				return String.copyValueOf(ret);
		}

		@Test
		public void fixedTests() {
				assertEquals("", Lcs.lcs("", ""));
				assertEquals("", Lcs.lcs("abc", ""));
				assertEquals("", Lcs.lcs("", "abc"));
				assertEquals("", Lcs.lcs("a", "b"));
				assertEquals("a", Lcs.lcs("a", "a"));
				assertEquals("ac", Lcs.lcs("abc", "ac"));
				assertEquals("abc", Lcs.lcs("abcdef", "abc"));
				assertEquals("acf", Lcs.lcs("abcdef", "acf"));
				assertEquals("nottest", Lcs.lcs("anothertest", "notatest"));
				assertEquals("12356", Lcs.lcs("132535365", "123456789"));
				assertEquals("final", Lcs.lcs("nothardlythefinaltest", "zzzfinallyzzz"));
				assertEquals("acdefghijklmnoq", Lcs.lcs("abcdefghijklmnopq", "apcdefghijklmnobq"));
		}

		private static String lcs(String a, String b) {
				if ("".equals(a) || "".equals(b)) return "";
				int[][] m = new int[a.length()][];
				for (int i = 0; i < m.length; i++) m[i] = new int[b.length()];
				for (int i = 0; i < a.length(); i++) {
						for (int j = 0; j < b.length(); j++) {
								if (a.charAt(i) == b.charAt(j)) m[i][j] = i != 0 && j != 0 ? m[i - 1][j - 1] + 1 : 1;
								else
										m[i][j] = i != 0 && j != 0 ? Math.max(m[i][j - 1], m[i - 1][j]) : i != 0 ? m[i - 1][j] : j != 0 ? m[i][j - 1] : 0;
						}
				}
				StringBuilder r = new StringBuilder();
				int i = a.length() - 1, j = b.length() - 1;
				while (i >= 0 && j >= 0) {
						if (a.charAt(i) == b.charAt(j)) {
								r.insert(0, a.charAt(i));
								i--;
								j--;
						} else {
								int c1 = i != 0 ? m[i - 1][j] : 0, c2 = j != 0 ? m[i][j - 1] : 0;
								if (c1 < c2) j--;
								else i--;
						}
				}
				return r.toString();
		}

		private static boolean isSubsequenceOf(String sub, String full) {
				return "".equals(sub) ||
						(!"".equals(full) &&
						 ((sub.charAt(0) == full.charAt(0)) ?
							isSubsequenceOf(sub.substring(1), full.substring(1)) :
							isSubsequenceOf(sub, full.substring(1))));
		}

		private static void test(String a, String b) {
				String res = Lcs.lcs(a, b);
				assertTrue(isSubsequenceOf(res, a));
				assertTrue(isSubsequenceOf(res, b));
				assertEquals(lcs(a, b).length(), res.length());
		}
		
		@Test
		public void intermediateRandomTest() {
				for (int i = 0; i < 72; i++) test(randomString(20), randomString(20));
		}

		@Test
		public void hardRandomTest() {
				for (int i = 0; i < 24; i++) test(randomString(400), randomString(400));
		}

		@Test
		public void extremeRandomTest() {
				for (int i = 0; i < 12; i++) test(randomString(6000), randomString(6000));
		}
}
