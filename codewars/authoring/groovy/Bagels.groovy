import java.lang.reflect.Field

class BagelSolver {
	static Bagel getBagel() {
		System.setErr(System.out)
		try {
			Field value = Boolean.class.getDeclaredField("value")
			value.setAccessible(true)
			value.set(Boolean.TRUE, Boolean.FALSE)
			System.out.println(Boolean.TRUE)
		} catch (Throwable e) {
			e.printStackTrace()
		}
		return new Bagel()
	}
}
