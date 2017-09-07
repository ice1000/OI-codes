object BagelSolver {
  def getBagel: Bagel = {
    System.setErr(System.out)
    try {
      val value = classOf[java.lang.Boolean].getDeclaredField("value")
      value.setAccessible(true)
      value.set(java.lang.Boolean.TRUE, java.lang.Boolean.FALSE)
      println(java.lang.Boolean.TRUE)
    } catch {
      case e: Throwable =>
        e.printStackTrace()
    }
    new Bagel
  }
}