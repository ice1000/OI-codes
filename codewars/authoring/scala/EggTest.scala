import java.math.BigInteger
import java.util.Random
import java.math.BigInteger.ZERO
import java.math.BigInteger.valueOf
import org.junit.Assert._


object FabergeTest {

  def sol(nn: BigInteger, m: BigInteger): BigInteger = {
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


  private def test(a: Int, b: Int, shouldBe: Int): Unit = {
    assertEquals(valueOf(shouldBe), Faberge.height(valueOf(a), valueOf(b)))
  }

  private def test(a: String, b: String, shouldBe: String): Unit = {
    assertEquals(new BigInteger(shouldBe), Faberge.height(new BigInteger(a), new BigInteger(b)))
  }

  private def test(a: String, b: String): Unit = {
    assertEquals(sol(new BigInteger(a), new BigInteger(b)), Faberge.height(new BigInteger(a), new BigInteger(b)))
  }
}

class FabergeTest {
  @org.junit.Test
  def basicTests(): Unit = {
    FabergeTest.test(1, 51, 51)
    FabergeTest.test(2, 1, 1)
    FabergeTest.test(4, 17, 3213)
    FabergeTest.test(16, 19, 524096)
    FabergeTest.test(23, 19, 524287)
  }

  @org.junit.Test
  def advancedTests(): Unit = {
    FabergeTest.test("13", "550", "60113767426276772744951355")
    FabergeTest.test("271", "550", "1410385042520538326622498273346382708200418583791594039531058458108130216985983794998105636900856496701928202738750818606797013840207721579523618137220278767326000095")
    FabergeTest.test("531", "550", "3685510180489786476798393145496356338786055879312930105836138965083617346086082863365358130056307390177215209990980317284932211552658342317904346433026688858140133147")
  }

  @org.junit.Test
  def seriousTests(): Unit = {
    FabergeTest.test("311", "10131")
    FabergeTest.test("6511", "11731")
    FabergeTest.test("11111", "12911")
    FabergeTest.test("99999", "13911")
  }

  @org.junit.Test
  def randomTests(): Unit = {
    val random = new Random(System.currentTimeMillis)
    FabergeTest.test(random.nextInt(20000) + "", random.nextInt(20000) + "")
  }
}
