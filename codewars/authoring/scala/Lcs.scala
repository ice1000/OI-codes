object Lcs {
  def lcs(a: String, b: String): String = {
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
}