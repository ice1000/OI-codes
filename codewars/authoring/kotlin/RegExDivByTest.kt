import org.junit.Assert.*
import org.junit.FixMethodOrder
import org.junit.Test
import org.junit.runners.MethodSorters
import java.io.File
import java.io.IOException
import java.nio.file.Files
import java.util.*
import java.util.regex.Pattern


@FixMethodOrder(MethodSorters.NAME_ASCENDING)
class SolutionTest {

	@Test
	fun test0_AntiCheat() = try {
		var length = 0
		Files.lines(File("/home/codewarrior/solution.txt").toPath()).forEach { line ->
			checkSourceLine(line)
			length += sourceLength(line)
		}
		assertTrue(arrayOf(
				"Seriously, you didn\'t believe me? You can\'t hard-code the answers! ",
				"Either that, or your solution is inefficient. Let\'s keep it under 5K, k? ",
				String.format("(Your code length: %d)", length)).joinToString(""),
				length < 5000)
	} catch (e: IOException) {
//		fail("Failed to read the source file.")
	}

	private fun checkSourceLine(line: String) {
		val pattern = Pattern.compile("([^a-zA-Z0-9_]|^)(System|io|regex|zip)([^a-zA-Z0-9_]|$)")
		val matcher = pattern.matcher(line)
		if (matcher.find()) {
			fail("You\'re asking for trouble... (You cannot use System, io, regex, zip in your code)")
		}
	}

	private fun sourceLength(line: String): Int {
		return line.trim { it <= ' ' }.length
	}

	@Test
	fun test1_MainTest() {
		for (n in 1..18) {
			testWithNumber(n)
		}
	}

	private fun testWithNumber(n: Int) {
		val regex = regexDivisibleBy(n)
		val random = Random()

		System.out.printf("Testing divisibility by %d...", n)
		assertFalse("Cannot be an empty string\n", regex == "")

		var pattern = Pattern.compile("[^01?*+^$:()\\[\\]|]")
		var matcher = pattern.matcher(regex)
		if (matcher.find()) {
			fail(String.format("Found an illegal character: %s\n", matcher.group()))
		}

		val invalidArgs = arrayOf(" ", String(Character.toChars(randInt(random, 97, 122))), String(Character.toChars(randInt(random, 33, 45))), Integer.toString(randInt(random, 12, 91)))
		val validArgs = intArrayOf(0, n, n * randInt(random, 2, 50), randInt(random, 0, 999), randInt(random, 1000, 1 shl 30), hardPositive(random, n))

		pattern = Pattern.compile(regex)
		for (invalidArg in invalidArgs) {
			matcher = pattern.matcher(invalidArg)
			assertFalse(String.format("Did not reject invalid input: %s\n", invalidArg),
					matcher.matches())
		}
		for (arg in validArgs) {
			val numberToMatch = Integer.toBinaryString(arg)
			matcher = pattern.matcher(numberToMatch)
			assertEquals(String.format("Did not give correct answer for the number: %d\n", arg),
					matcher.matches(), arg % n == 0)
		}
		println(" Passed!")
	}

	private fun randInt(random: Random, min: Int, max: Int): Int {
		return random.nextInt(max - min + 1) + min
	}

	private fun hardPositive(random: Random, n: Int): Int {
		return (1 shl randInt(random, 22, 30)) / n * n + n
	}
}
