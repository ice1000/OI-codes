import org.junit.Test;

import java.util.Random;

import static org.junit.Assert.assertEquals;

public class KataTest {
	@Test
	public void sampleTest() {
		assertEquals("128.114.17.104", Kata.longToIP(2154959208L));
		assertEquals("0.0.0.0", Kata.longToIP(0));
		assertEquals("128.32.10.1", Kata.longToIP(2149583361L));
	}

	private static Random random = new Random();

	private static String solution(long ip) {
		return (ip >>> 24) % 256 + "." + (ip >>> 16) % 256 + "." + (ip >>> 8) % 256 + "." + ip % 256;
	}

	@Test
	public void randomTest() {
		final int Tests = 100;
		for (int i = 0; i < Tests; ++i) {
			long thirtyBits = random.nextInt(1 << 30);
			long twoBits = random.nextInt(1 << 2);
			long fullRange = (thirtyBits << 2) | twoBits;

			String expected = solution(fullRange);
			String actual = Kata.longToIP(fullRange);

			assertEquals(expected, actual);
		}
	}
}