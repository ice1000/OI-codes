package codewars;

import org.junit.Test;

import java.util.Arrays;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

import static codewars.ISO.*;
import static org.junit.Assert.*;

/**
 * Created by ice1000 on 17-6-19.
 *
 * @author ice1000
 */
@SuppressWarnings("AssertEqualsBetweenInconvertibleTypes")
public class ISOTest {
	private static <A, B> ISO<A, B> iso(Function<A, B> forward, Function<B, A> backward) {
		return new ISO<A, B>() {
			@Override
			public A bw(B b) {
				return backward.apply(b);
			}

			@Override
			public B fw(A a) {
				return forward.apply(a);
			}
		};
	}

	interface Lambda {
		void apply();
	}

	private static void assertThrows(Class<? extends Throwable> clazz, Lambda function) {
		try {
			function.apply();
		} catch (Throwable e) {
			if (clazz != e.getClass())
				fail(String.format("Error: expected: %s, get: %s", clazz, e.getClass()));
			return;
		}
		fail("No exceptions thrown!");
	}

	private static final String MEOW = "meow";
	private static final String MOE = "moe";

	private static ISO<Boolean, String> tISO = iso(it -> it ? MEOW : MOE, MEOW::equals);

	private static ISO<Optional<Boolean>, Optional<Boolean>> mISO = iso(it -> it.<Optional<Boolean>>map(b -> b
			? Optional.of(false)
			: Optional.empty()).orElse(Optional.of(true)), null);

	private static ISO<Boolean, Boolean> bISO = isoUnOptional(mISO);

	private static ISO<Optional<Boolean>, Optional<Boolean>> badMISO = iso(it -> it.flatMap(b -> b
			? Optional.of(false)
			: Optional.empty()), null);

	private static ISO<Boolean, Boolean> badISO = isoUnOptional(badMISO);

	private static <A, B> Function<A, A> lrl(ISO<A, B> iso) {
		return it -> iso.bw(iso.fw(it));
	}

	private static <A, B> Function<B, B> rlr(ISO<A, B> iso) {
		return it -> iso.fw(iso.bw(it));
	}

	private static final String str = "it was me, DIO!";

	private static Stream<Object> lu = Arrays.stream(new Object[]{0, 1, 2, 3, 4, 5, 6, 7});

	@Test
	public void subStLTest() {
		assertEquals(MEOW, subStL(tISO).apply(true));
		assertEquals(false, subStL(isoBool()).apply(false));
		assertEquals(true, subStL(isoBool()).apply(true));
	}

	@Test
	public void subStRTest() {
		assertEquals(MEOW, subStL(subStR(iso(null, e -> tISO)).apply(null)).apply(true));
		assertEquals(true, subStR(isoBool()).apply(true));
		assertEquals(false, subStR(isoBool()).apply(false));
	}

	@Test
	@SuppressWarnings("unchecked")
	public void reflTest() {
		assertEquals(MEOW, subStL((ISO<Boolean, Boolean>) subStL(refl()).apply(tISO)).apply(true));
	}

	@Test
	public void symmTest() {
		assertEquals(MEOW, subStR(symm(tISO)).apply(true));
	}

	@Test
	public void transTest() {
		assertEquals(MEOW, subStL(trans(refl(), trans(tISO, refl()))).apply(true));
	}

	@Test
	public void isoTupleTest() {
		Tuple<String, String> tuple = subStL(isoTuple(tISO, tISO)).apply(new Tuple<>(true, false));
		assertEquals(MEOW, tuple.a);
		assertEquals(MOE, tuple.b);
	}

	@Test
	public void isoStreamTest() {
		assertEquals(Optional.of(MEOW + MEOW + MOE),
				subStL(isoStream(tISO)).apply(Arrays.stream(new Boolean[]{true, true, false}))
						.reduce((a, b) -> a + b));
	}

	@Test
	public void isoFuncTest() {
		assertEquals(MEOW, subStL(isoFunc(symm(tISO), tISO)).apply(MEOW::equals).apply(true));
	}

	@Test
	@SuppressWarnings("ConstantConditions")
	public void isoOptionalTest() {
		assertFalse(subStL(isoOptional(tISO)).apply(Optional.empty()).isPresent());
		assertEquals(MEOW, subStL(isoOptional(tISO)).apply(Optional.of(true)).get());
	}

	@Test
	public void isoUnOptionalTest() {
		assertEquals(false, subStL(bISO).apply(true));
		assertEquals(true, subStL(bISO).apply(false));
		assertEquals(false, subStL(badISO).apply(true));
		assertThrows(NoSuchElementException.class, () -> subStL(badISO).apply(false));
	}

	public static boolean eitherEq(Either<?, ?> a, Either<?, ?> b) {
		return Objects.equals(a.l, b.l) && Objects.equals(a.r, b.r);
	}

	@Test
	@SuppressWarnings("unchecked")
	public void isoEitherTest() {
		assertTrue(eitherEq(Either.left(false), subStL(isoEither(isoBoolNot(), tISO))
				.apply(Either.left(true))));
		assertTrue(eitherEq(Either.left(true), subStL(isoEither(isoBoolNot(), tISO))
				.apply(Either.left(false))));
		assertTrue(eitherEq(Either.right(MEOW), subStL(isoEither(isoBoolNot(), tISO))
				.apply(Either.right(true))));
	}

	@Test
	@SuppressWarnings("unchecked")
	public void isoSymmTest() {
		assertEquals(MOE, subStR(subStR(isoSymm()).apply((ISO) tISO)).apply(false));
	}
}