import java.util.stream.IntStream;

/**
 * Created by ice1000 on 17-6-29.
 *
 * @author ice1000
 */
public class Primes {
		public static IntStream stream() {
				return IntStream
						.concat(IntStream.of(2), IntStream.iterate(3, (last) -> last + 2))
						.filter(integer -> {
										for (int i = 3, limit = (int) Math.sqrt(integer); i <= limit; i += 2) if (integer % i == 0) return false;
										return true;
								});
		}
}
