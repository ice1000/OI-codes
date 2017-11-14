import org.junit.Assert.assertFalse
import java.io.File
import java.nio.BufferOverflowException
import java.nio.file.Files
import java.util.*
import kotlin.test.assertFailsWith

/**
 * Created by ice1000 on 17-6-16.
 *
 * @author ice1000
 */
class ThrowWithoutThrowingTest {
	@org.junit.Test
	fun tests() {
		assertFailsWith(ArithmeticException::class, ::arithmetic)
		assertFailsWith(NoSuchElementException::class, ::noSuchElement)
		assertFailsWith(ArrayIndexOutOfBoundsException::class, ::arrayIndexOutOfBound)
		assertFailsWith(ClassCastException::class, ::classCast)
		assertFailsWith(StackOverflowError::class, ::stackOverflow)
		assertFailsWith(NullPointerException::class, ::nullPointer)
		assertFailsWith(NumberFormatException::class, ::numberFormat)
		assertFailsWith(IllegalArgumentException::class, ::illegalArgument)
		assertFailsWith(NegativeArraySizeException::class, ::negativeArraySize)
		assertFailsWith(EmptyStackException::class, ::emptyStack)
		assertFailsWith(BufferOverflowException::class, ::bufferOverflow)
		assertFailsWith(ArrayStoreException::class, ::arrayStore)
		assertFailsWith(UnsupportedOperationException::class, ::unsupportedOperation)
		assertFailsWith(IllegalStateException::class, ::illegalState)
	}

	@org.junit.Test
	fun notUsingThrow() {
		Files.lines(File("/home/codewarrior/solution.txt").toPath()).forEach { str ->
			assertFalse("Exception" in str)
			assertFalse("Error" in str)
			assertFalse("Throwable" in str)
			assertFalse("Class" in str)
			assertFalse("throw" in str)
			assertFalse("\\u" in str)
		}
	}
}