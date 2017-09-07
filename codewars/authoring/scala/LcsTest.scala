import java.util.Random

import org.junit.Assert._
import org.junit.Test

object LcsTest {
  private val r = new Random(System.currentTimeMillis)

  private def randomString(len: Int) = {
    val i = new Array[Int](len)
    var index = 0
    while (index < i.length) {
      i(index) = r.nextInt(26) + 97
      index += 1
    }
    val ret = new Array[Char](len)
    var j = 0
    while (j < i.length) {
      ret(j) = i(j).toChar
      j += 1
    }
    String.copyValueOf(ret)
  }

  private def lcs(a: String, b: String): String = {
    if ("" == a || "" == b) return ""
    val m = new Array[Array[Int]](a.length)
    var i: Int = 0
    while (i < m.length) {
      m(i) = new Array[Int](b.length)
      i += 1
    }
    i = 0
    while (i < a.length) {
      var j: Int = 0
      while (j < b.length) {
        if (a.charAt(i) == b.charAt(j)) m(i)(j) = if (i != 0 && j != 0) m(i - 1)(j - 1) + 1 else 1
        else m(i)(j) = if (i != 0 && j != 0) Math.max(m(i)(j - 1), m(i - 1)(j))
        else if (i != 0) m(i - 1)(j) else if (j != 0) m(i)(j - 1) else 0
        j += 1
      }
      i += 1
    }
    val r = new StringBuilder
    i = a.length - 1
    var j = b.length - 1
    while (i >= 0 && j >= 0) if (a.charAt(i) == b.charAt(j)) {
      r.insert(0, a.charAt(i))
      i -= 1
      j -= 1
    }
    else {
      val x = if (i != 0) m(i - 1)(j) else 0
      val y = if (j != 0) m(i)(j - 1) else 0
      if (x < y) j -= 1 else i -= 1
    }
    r.toString
  }

  private def isSubsequenceOf(sub: String, full: String): Boolean = "" == sub || (!("" == full) && (
    if (sub.charAt(0) == full.charAt(0)) isSubsequenceOf(sub.substring(1), full.substring(1))
    else isSubsequenceOf(sub, full.substring(1))))

  def test(a: String, b: String) = {
    val res = Lcs.lcs(a, b)
    assertTrue(isSubsequenceOf(res, a))
    assertTrue(isSubsequenceOf(res, b))
    assertEquals(lcs(a, b).length, res.length)
  }
}

class LcsTest {
  @Test def fixedTests(): Unit = {
    assertEquals("", Lcs.lcs("", ""))
    assertEquals("", Lcs.lcs("abc", ""))
    assertEquals("", Lcs.lcs("", "abc"))
    assertEquals("", Lcs.lcs("a", "b"))
    assertEquals("a", Lcs.lcs("a", "a"))
    assertEquals("ac", Lcs.lcs("abc", "ac"))
    assertEquals("abc", Lcs.lcs("abcdef", "abc"))
    assertEquals("acf", Lcs.lcs("abcdef", "acf"))
    assertEquals("nottest", Lcs.lcs("anothertest", "notatest"))
    assertEquals("12356", Lcs.lcs("132535365", "123456789"))
    assertEquals("final", Lcs.lcs("nothardlythefinaltest", "zzzfinallyzzz"))
    assertEquals("acdefghijklmnoq", Lcs.lcs("abcdefghijklmnopq", "apcdefghijklmnobq"))
  }

  @Test def intermediateRandomTest(): Unit = {
    var i = 0
    while (i < 72) {
      LcsTest.test(LcsTest.randomString(20), LcsTest.randomString(20))
      i += 1
    }
  }

  @Test def hardRandomTest(): Unit = {
    var i = 0
    while (i < 24) {
      LcsTest.test(LcsTest.randomString(400), LcsTest.randomString(400))
      i += 1
    }
  }

  @Test def extremeRandomTest(): Unit = {
    var i = 0
    while (i < 12) {
      LcsTest.test(LcsTest.randomString(2000), LcsTest.randomString(2000))
      i += 1
    }
  }
}