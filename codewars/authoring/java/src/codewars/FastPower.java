package codewars;

/**
 * Created by ice1000 on 17-7-3.
 *
 * @author ice1000
 */
public class FastPower {
	/** When it's true, the log will be printed. */
	public static final boolean DEBUG = false;

	private static long plus(long a, long b, long m) {
		long s = a + b;
		if (s >= a && s >= b) return s % m;
		if (a > m) return plus(a % m, b, m);
		if (b > m) return plus(a, b % m, m);
		return a - m + b;
	}

	private static long mul(long a, long b, long m) {
		long ret = 0;
		while (b != 0) {
			if ((b & 1) != 0) ret = plus(ret, a, m);
			b >>>= 1;
			a = plus(a, a, m);
		}
		return ret;
	}

	public static long pow(long a, long b, long m) {
		long ret = 1;
		while (b != 0) {
			if ((b & 1) != 0) ret = mul(ret, a, m);
			b >>>= 1;
			a = mul(a, a, m);
		}
//		Math.pow(a, b) % m
		return ret;
	}
}
