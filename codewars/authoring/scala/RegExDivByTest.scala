import java.io.IOException
import java.nio.file.Files
import java.util.Random
import java.util.regex.Pattern
import java.io.File
import java.util.function.Consumer

import org.junit.Assert.{assertFalse, fail}
import org.junit.Test
import org.junit.Assert.assertEquals
import org.junit.Assert.assertTrue


class DivByNTest {

  @Test
  def test0_AntiCheat() = {
    var length = 0
    Files.lines(new File("/home/codewarrior/solution.txt").toPath).forEach(new Consumer[String] {
      override def accept(line: String): Unit = {
        checkSourceLine(line)
        length += sourceLength(line)
      }
    })
    assertTrue("Seriously, you didn\'t believe me? You can\'t hard-code the answers! " +
      "Either that, or your solution is inefficient. Let\'s keep it under 5K, k? " +
      "(Your code length: " + length + ")",
      length < 5000)
  }

  private def checkSourceLine(line: String) = {
    val pattern = Pattern.compile("([^a-zA-Z0-9_]|^)(System|io|regex|zip)([^a-zA-Z0-9_]|$)")
    val matcher = pattern.matcher(line)
    if (matcher.find) fail("You\'re asking for trouble... (You cannot use System, io, regex, zip in your code)")
  }

  private def sourceLength(line: String) = line.trim.length

  @Test def test1_MainTest(): Unit = {
    var n = 1
    while (n <= 18) {
      testWithNumber(n)
      n += 1
    }
  }

  private def testWithNumber(n: Int) = {
    val solution = new Solution
    val regex = solution.regexDivisibleBy(n)
    val random = new Random
    printf("Testing divisibility by %d...", n)
    assertFalse("Cannot be an empty string\n", regex == "")
    var pattern = Pattern.compile("[^01?*+^$:()\\[\\]|]")
    var matcher = pattern.matcher(regex)
    if (matcher.find) fail(String.format("Found an illegal character: %s\n", matcher.group))
    val invalidArgs = Array[String](" ", new String(Character.toChars(randInt(random, 97, 122))), new String(Character.toChars(randInt(random, 33, 45))), Integer.toString(randInt(random, 12, 91)))
    val validArgs = Array[Int](0, n, n * randInt(random, 2, 50), randInt(random, 0, 999), randInt(random, 1000, 1 << 30), hardPositive(random, n))
    pattern = Pattern.compile(regex)
    for (invalidArg <- invalidArgs) {
      matcher = pattern.matcher(invalidArg)
      assertFalse(String.format("Did not reject invalid input: %s\n", invalidArg), matcher.matches)
    }
    for (arg <- validArgs) {
      val numberToMatch = Integer.toBinaryString(arg)
      matcher = pattern.matcher(numberToMatch)
      assertEquals("Did not give correct answer for the number: " + arg + "\n", matcher.matches, arg % n == 0)
    }
    println(" Passed!")
  }

  private def randInt(random: Random, min: Int, max: Int) = random.nextInt(max - min + 1) + min

  private def hardPositive(random: Random, n: Int) = (1 << randInt(random, 22, 30)) / n * n + n
}