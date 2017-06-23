package codewars;

import java.io.File;
import java.nio.BufferOverflowException;
import java.nio.file.Files;
import java.util.EmptyStackException;
import java.util.NoSuchElementException;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.fail;

/**
 * Created by ice1000 on 17-6-16.
 *
 * @author ice1000
 */
public class ThrowWithoutThrowingTest {
	@org.junit.Test
	public void tests() throws Exception {
		assertThrows(ArithmeticException.class, ThrowWithoutThrowing::arithmetic);
		assertThrows(NoSuchElementException.class, ThrowWithoutThrowing::noSuchElement);
		assertThrows(ArrayIndexOutOfBoundsException.class, ThrowWithoutThrowing::arrayIndexOutOfBound);
		assertThrows(ClassCastException.class, ThrowWithoutThrowing::classCast);
		assertThrows(StackOverflowError.class, ThrowWithoutThrowing::stackOverflow);
		assertThrows(NullPointerException.class, ThrowWithoutThrowing::nullPointer);
		assertThrows(NumberFormatException.class, ThrowWithoutThrowing::numberFormat);
		assertThrows(IllegalArgumentException.class, ThrowWithoutThrowing::illegalArgument);
		assertThrows(NegativeArraySizeException.class, ThrowWithoutThrowing::negativeArraySize);
		assertThrows(EmptyStackException.class, ThrowWithoutThrowing::emptyStack);
		assertThrows(BufferOverflowException.class, ThrowWithoutThrowing::bufferOverflow);
		assertThrows(ArrayStoreException.class, ThrowWithoutThrowing::arrayStore);
		assertThrows(UnsupportedOperationException.class, ThrowWithoutThrowing::unsupportedOperation);
		assertThrows(IllegalStateException.class, ThrowWithoutThrowing::illegalState);
	}

	@org.junit.Test
	public void notUsingThrow() throws Exception {
//		Files.lines(new File("/home/codewarrior/solution.txt").toPath()).forEach(str -> {
		Files.lines(new File("./src/main/ThrowWithoutThrowing.java").toPath()).forEach(str -> {
			assertFalse(str.contains("Exception"));
			assertFalse(str.contains("Error"));
			assertFalse(str.contains("Throwable"));
			assertFalse(str.contains("Class"));
			assertFalse(str.contains("throw"));
			assertFalse(str.contains("\\u"));
		});
	}

	interface Lambda {
		void apply();
	}

	private static void assertThrows(Class<? extends Throwable> clazz, Lambda function) {
		try {
			function.apply();
		} catch (Throwable e) {
			if (e.getClass() == clazz) System.out.println("Successfully thrown " + e.getClass().getSimpleName()
					+ ", message: " + e.getMessage());
			else fail("Error: expected: " + clazz.getSimpleName() + ", get: " + e.getClass().getSimpleName());
			return;
		}
		fail("No exceptions thrown!");
	}
}