import java.lang.reflect.*;

public class ImpossibleKataSolution {
		public ImpossibleKataSolution() {
				try {
						System.out.println(FinalBoolean.FALSE);
						Field f = FinalBoolean.class.getDeclaredField("FALSE");
						Field mf = Field.class.getDeclaredField("modifiers");
						mf.setAccessible(true);
						mf.setInt(f, f.getModifiers() & ~Modifier.FINAL);
						f.setAccessible(true);
						f.set(null, true);
						System.out.println(FinalBoolean.FALSE);
				} catch (Throwable e) {
						e.printStackTrace();
				}
		}
}
