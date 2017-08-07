import java.math.BigInteger;

import static java.math.BigInteger.ZERO;
import static java.math.BigInteger.valueOf;

public class Faberge {
	public static BigInteger height(BigInteger n, BigInteger m) {
		if (n.equals(ZERO) || m.equals(ZERO)) return ZERO;
		if (n.compareTo(m) > 0) n = m;
		BigInteger c = valueOf(1);
		BigInteger b = valueOf(1);
		BigInteger a = valueOf(0);
		while (c.compareTo(n) <= 0) {
			BigInteger d = m.add(valueOf(1)).subtract(c).multiply(b).divide(c);
			c = c.add(valueOf(1));
			b = d;
			a = a.add(d);
		}
		return a;
	}
}
