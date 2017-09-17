import org.junit.Test
import java.io.File
import java.io.IOException
import java.nio.file.Files
import java.util.*
import kotlin.test.*

class KotlinTricks3 {
	@Test
	fun cannotUseFun() = try {
		Files.lines(File("/home/codewarrior/solution.txt").toPath()).forEach { line ->
			assertFalse { "fun" in line }
		}
	} catch (e: IOException) {
		fail("Failed to read the source file.")
	}

	@Test
	fun fixedTest() {
		assertEquals("ice1000", concatString("ice", "1000"))
	}

	@Test
	fun randomTest() {
		val r = Random(System.currentTimeMillis())
		(0..100).forEach {
			val a = r.nextInt().toString(2)
			val b = r.nextInt().toString(2)
			assertEquals(a + b, concatString(a, b))
		}
	}
}
