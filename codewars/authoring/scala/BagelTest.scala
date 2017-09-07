import org.junit.Assert.assertEquals
import org.junit.Test

class BagelTest {
  @Test def testBagel(): Unit = {
    assertEquals(BagelSolver.getBagel.getValue == 4, java.lang.Boolean.TRUE)
  }
}