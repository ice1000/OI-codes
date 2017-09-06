import java.math.BigInteger
import java.math.BigInteger.ZERO
import java.math.BigInteger.valueOf

object Faberge {
  def height(nn: BigInteger, m: BigInteger): BigInteger = {
    var n: BigInteger = nn
    if (n == ZERO || m == ZERO) return ZERO
    if (n.compareTo(m) > 0) n = m
    var c = valueOf(1)
    var b = valueOf(1)
    var a = valueOf(0)
    while ( {
      c.compareTo(n) <= 0
    }) {
      val d = m.add(valueOf(1)).subtract(c).multiply(b).divide(c)
      c = c.add(valueOf(1))
      b = d
      a = a.add(d)
    }
    a
  }
}
