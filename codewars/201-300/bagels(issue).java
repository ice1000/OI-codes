import java.lang.reflect.Field;
import java.lang.instrument.*;
import java.security.*;
import sun.misc.Unsafe;

public class BagelSolver {

		public static Bagel getBagel() {
				try {
						Field f = Boolean.class.getDeclaredField("TRUE");
						Field u = Unsafe.class.getDeclaredField("theUnsafe");
						u.setAccessible(true);
						Unsafe unsafe = (Unsafe) u.get(null);
						Object gay = unsafe.staticFieldBase(f);
						long offset = unsafe.staticFieldOffset(f);
						System.out.println(Boolean.TRUE);
						unsafe.putObject(gay, offset, Boolean.FALSE);
						System.out.println(Boolean.TRUE);
				} catch (Throwable e) {
						e.printStackTrace();
				}
				return new Bagel();
		}
}

