import org.junit.Test
import java.util.Random
import org.junit.Assert.assertEquals
import org.junit.Assert.fail

object TestFixture {
  protected def AssertComplexEquals(expected: Array[Double], actual: Array[Double]): Unit = {
    if (Math.abs(expected(0)) <= 1) assertEquals("The real part of your returned complex number is not sufficiently close to the expected value", actual(0), expected(0), 1e-12)
    else assertEquals("The real part of your returned complex number is not sufficiently close to the expected value", actual(0), expected(0), 1e-10)
    if (Math.abs(expected(1)) <= 1) assertEquals("The imaginary part of your returned complex number is not sufficiently close to the expected value", actual(1), expected(1), 1e-12)
    else assertEquals("The imaginary part of your returned complex number is not sufficiently close to the expected value", actual(1), expected(1), 1e-10)
  }

  def sol(complex: Array[Double]): Array[Double] = Array[Double](Math.log(Math.sqrt(complex(0) * complex(0) + complex(1) * complex(1))), Math.atan2(complex(1), complex(0)))

  def assertThrows(clazz: Class[_ <: Throwable], function: () => Unit): Unit = {
    try function()
    catch {
      case e: Throwable =>
        if (e.getClass eq clazz) System.out.println("Successfully thrown " + e.getClass.getSimpleName + ", message: " + e.getMessage)
        else fail("Error: expected: " + clazz.getSimpleName + ", get: " + e.getClass.getSimpleName)
        return
    }
    fail("No exceptions thrown!")
  }

  protected var RandGen = new Random
}

class TestFixture {
  @Test def ExampleTests(): Unit = {
    TestFixture.AssertComplexEquals(Array[Double](2.995732273553991, 0), Logger.log(Array[Double](20, 0)))
    TestFixture.AssertComplexEquals(Array[Double](0, 3.141592653589793), Logger.log(Array[Double](-1, 0)))
    TestFixture.AssertComplexEquals(Array[Double](0.346573590279973, 0.785398163397448), Logger.log(Array[Double](1, 1)))
    TestFixture.assertThrows(classOf[ArithmeticException], () => Logger.log(Array[Double](0, 0)))
  }

  @Test def FixedTests(): Unit = {
    TestFixture.AssertComplexEquals(Array[Double](3.218875824868201, 2.857798544381465), Logger.log(Array[Double](-24, 7)))
    TestFixture.AssertComplexEquals(Array[Double](0, 1.570796326794897), Logger.log(Array[Double](0, 1)))
    TestFixture.AssertComplexEquals(Array[Double](0, 0), Logger.log(Array[Double](1, 0)))
    TestFixture.AssertComplexEquals(Array[Double](1.598433436873693, 0.463447163733142), Logger.log(Array[Double](8834d / 1997d, 93387d / 42243d)))
    TestFixture.AssertComplexEquals(Array[Double](11.275831160977204, 1.203262110987354), Logger.log(Array[Double](28347, 73623)))
    // Let's test this edge case one more time ;)
    TestFixture.assertThrows(classOf[ArithmeticException], () => Logger.log(Array[Double](0.0, 0.0)))
  }

  @Test def RandomTests(): Unit = {
    var i = 0
    while ( {
      i < 100
    }) {
      val z = Array[Double](-5e3 + 1e4 * TestFixture.RandGen.nextDouble, -5e3 + 1e4 * TestFixture.RandGen.nextDouble)
      System.out.println("Testing for z = " + z(0) + " + " + z(1) + "i")
      TestFixture.AssertComplexEquals(TestFixture.sol(z), Logger.log(z))
      i += 1
      i - 1

    }
  }
}
