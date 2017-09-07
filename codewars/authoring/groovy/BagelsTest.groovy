import org.junit.Test

import static org.junit.Assert.assertEquals

class BagelTest {
	@Test
	void testBagel() {
		assertEquals(BagelSolver.getBagel().getValue() == 4, java.lang.Boolean.TRUE)
	}
}