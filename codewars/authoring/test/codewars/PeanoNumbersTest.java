package codewars;

import codewars.PeanoNumbers.Peano.Succ;
import codewars.PeanoNumbers.Peano.Zero;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

import static codewars.PeanoNumbers.Ordering.*;
import static codewars.PeanoNumbers.*;
import static org.junit.Assert.*;

/**
 * Created by ice1000 on 17-6-22.
 *
 * @author ice1000
 */
public class PeanoNumbersTest {
	interface Lambda {
		void apply();
	}

	private static void assertThrows(String msg, Class<? extends Throwable> clazz, Lambda function) {
		try {
			function.apply();
		} catch (Throwable e) {
			if (e.getClass() != clazz || !e.getMessage().equals(msg))
				fail("Error: expected: " + clazz.getSimpleName() + ", get: "
						+ e.getClass().getSimpleName() + ": " + e.getMessage());
			return;
		}
		fail("No exceptions thrown!");
	}

	private static Peano peano(int n) {
		if (0 == n) return Zero.INSTANCE;
		return new Succ(peano(n - 1));
	}

	private static void assertPeanoEq(Peano a, Peano b) {
		assertEquals(EQ, compare(a, b));
	}

	@Test
	public void addTest() throws Exception {
		assertPeanoEq(peano(0), add(peano(0), peano(0)));
		assertPeanoEq(peano(664), add(peano(0), peano(664)));
		assertPeanoEq(peano(90), add(peano(90), peano(0)));
		assertPeanoEq(peano(223), add(peano(99), peano(124)));
		assertPeanoEq(peano(687), add(peano(453), peano(234)));
	}

	@Test
	public void subTest() throws Exception {
		assertThrows("negative number", ArithmeticException.class,
				() -> sub(peano(0), peano(5)));
		assertThrows("negative number", ArithmeticException.class,
				() -> sub(peano(324), peano(355)));
		assertPeanoEq(peano(0), sub(peano(0), peano(0)));
		assertPeanoEq(peano(10), sub(peano(10), peano(0)));
		assertPeanoEq(peano(0), sub(peano(99), peano(99)));
		assertPeanoEq(peano(146), sub(peano(213), peano(67)));
	}

	@Test
	public void mulTest() throws Exception {
		assertPeanoEq(peano(0), mul(peano(0), peano(0)));
		assertPeanoEq(peano(0), mul(peano(5), peano(0)));
		assertPeanoEq(peano(0), mul(peano(0), peano(5)));
		assertPeanoEq(peano(2278), mul(peano(34), peano(67)));
		assertPeanoEq(peano(11016), mul(peano(34), peano(324)));
	}

	@Test
	public void divTest() throws Exception {
		assertThrows("divide by 0", ArithmeticException.class,
				() -> div(peano(0), peano(0)));
		assertThrows("divide by 0", ArithmeticException.class,
				() -> div(peano(33), peano(0)));
		assertPeanoEq(peano(4), div(peano(8), peano(2)));
		assertPeanoEq(peano(3), div(peano(10), peano(3)));
		assertPeanoEq(peano(2), div(peano(56), peano(23)));
		assertPeanoEq(peano(100), div(peano(1000), peano(10)));
	}

	@Test
	public void evenTest() throws Exception {
		assertTrue(even(peano(0)));
		assertTrue(even(peano(8)));
		assertFalse(even(peano(13)));
		assertFalse(even(peano(207)));
		assertTrue(even(peano(402)));
	}

	@Test
	public void oddTest() throws Exception {
		assertFalse(odd(peano(0)));
		assertFalse(odd(peano(8)));
		assertTrue(odd(peano(13)));
		assertTrue(odd(peano(207)));
		assertFalse(odd(peano(402)));
	}

	@Test
	public void compareTest() throws Exception {
		assertEquals(LT, compare(peano(0), peano(4)));
		assertEquals(LT, compare(peano(34), peano(67)));
		assertEquals(GT, compare(peano(210), peano(43)));
		assertEquals(GT, compare(peano(56), peano(13)));
		assertEquals(EQ, compare(peano(0), peano(0)));
		assertEquals(EQ, compare(peano(34), peano(34)));
	}

	@Test
	public void shouldntCheat() throws IOException {
		Files.lines(new File("/home/codewarrior/solution.txt").toPath()).forEach(str -> {
			assertFalse(str.contains("+"));
			assertFalse(str.contains("-"));
			assertFalse(str.contains("*"));
			assertFalse(str.contains("/"));
			assertFalse(str.contains("%"));
		});
	}

}