import org.junit.Test
import java.util.*
import kotlin.test.assertEquals

class KotlinTricks0 {
	@Test
	fun testInt() {
		val r = Random(System.currentTimeMillis())
		(0..100).forEach { r.nextInt().let { assertEquals(it, kotlin.Int(it.toString())) } }
	}
	@Test
	fun testLong() {
		val r = Random(System.currentTimeMillis())
		(0..100).forEach { r.nextLong().let { assertEquals(it, kotlin.Long(it.toString())) } }
	}
	@Test
	fun testDouble() {
		val r = Random(System.currentTimeMillis())
		(0..100).forEach { r.nextDouble().let { assertEquals(it, kotlin.Double(it.toString())) } }
	}
}