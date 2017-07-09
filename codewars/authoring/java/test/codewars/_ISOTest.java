package codewars;

import org.junit.Test;

import java.util.stream.Collectors;
import java.util.List;
import java.util.Arrays;
import java.util.NoSuchElementException;
import java.util.Objects;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;
 
import static codewars.ISO.*;
import static org.junit.Assert.*;

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

		private static ISO<Boolean, String> tISO = 
				iso(it -> it ? MEOW : MOE, MEOW::equals);

		private static ISO<Optional<Boolean>, Optional<Boolean>> mISO = 
				iso(it -> it.<Optional<Boolean>>map
						(b -> b
						 ? Optional.of(false)
						 : Optional.empty()).orElseGet(() -> Optional.of(true)), null);
		
		private static ISO<Boolean, Boolean> bISO = 
				isoUnOptional(mISO);

		private static ISO<Optional<Boolean>, Optional<Boolean>> badMISO = 
				iso(it -> it.flatMap(b -> b
														 ? Optional.of(false)
														 : Optional.empty()), null);

		private static ISO<Boolean, Boolean> badISO = 
				isoUnOptional(badMISO);

		private static <A, B> Function<A, A> lrl(ISO<A, B> iso) {
				return it -> iso.bw(iso.fw(it));
		}

		private static <A, B> Function<B, B> rlr(ISO<A, B> iso) {
				return it -> iso.fw(iso.bw(it));
		}

		private static final String str = "it was me, DIO!";

		private static Stream<Object> lu =
				Arrays.stream(new Object[]{0, 1, 2, 3, 4, 5, 6, 7});

		@Test
		public void subStLTest() {
				assertEquals(MEOW, subStL(tISO).apply(true));
				assertEquals(false, subStL(isoBool()).apply(false));
				assertEquals(true, subStL(isoBool()).apply(true));
		}

		@Test
		public void subStRTest() {
				assertEquals(MEOW,
										 subStL(subStR(iso(null, e -> tISO)).apply(null)).apply(true));
				assertEquals(true, subStR(isoBool()).apply(true));
				assertEquals(false, subStR(isoBool()).apply(false));
		}

		@Test
		public void reflTest() {
				assertEquals(MEOW,
										 subStL((ISO<Boolean, Boolean>) subStL(refl())
														.apply(tISO)).apply(true));
		}

		@Test
		public void symmTest() {
				assertEquals(MEOW, subStR(symm(tISO)).apply(true));
		}

		@Test
		public void transTest() {
				assertEquals(MEOW, 
										 subStL(trans(refl(), trans(tISO, refl()))).apply(true));
		}
		
		@Test
		public void isoTupleTest() {
				Tuple<String, String> tuple =
						subStL(isoTuple(tISO, tISO)).apply(new Tuple<>(true, false));
				assertEquals(MEOW, tuple.a);
				assertEquals(MOE, tuple.b);
		}

		@Test
		public void isoStreamTest() {
				assertEquals(Optional.of(MEOW + MEOW + MOE),
										 subStL(isoStream(tISO)).apply(Arrays.stream
																									 (new Boolean[]{true, true, false}))
										 .reduce((a, b) -> a + b));
		}

		@Test
		public void isoFuncTest() {
				assertEquals(
										 MEOW,
										 subStL(isoFunc(symm(tISO), tISO)).apply(MEOW::equals)
										 .apply(true));
		}

		@Test
		public void isoOptionalTest() {
				assertFalse(subStL(isoOptional(tISO)).apply(Optional.empty()).isPresent());
				assertEquals(MEOW, 
										 subStL(isoOptional(tISO)).apply(Optional.of(true)).get());
		}

		@Test
		public void isoUnOptionalTest() {
				assertEquals(false, subStL(bISO).apply(true));
				assertEquals(true, subStL(bISO).apply(false));
				assertEquals(false, subStL(badISO).apply(true));
				assertThrows(NoSuchElementException.class, 
										 () -> subStL(badISO).apply(false));
				ISO<Boolean, Boolean> bi = isoUnOptional(isoOptional(refl()));
				assertEquals(true, lrl(bi).apply(true));
				assertEquals(false, lrl(bi).apply(false));
				assertEquals(true, rlr(bi).apply(true));
				assertEquals(false, rlr(bi).apply(false));
				ISO<Boolean, Boolean> biso = 
						symm(isoUnOptional(symm(mISO)));
				assertEquals(false, subStL(bISO).apply(true));
				assertEquals(true, subStL(bISO).apply(false));
				assertEquals(false, subStL(badISO).apply(true));
				assertThrows(NoSuchElementException.class, 
										 () -> subStL(badISO).apply(false));
		}

		Stream<Unit> lu() {
				return Stream.of
						(Unit.INSTANCE, Unit.INSTANCE,
						 Unit.INSTANCE, Unit.INSTANCE,
						 Unit.INSTANCE, Unit.INSTANCE,
						 Unit.INSTANCE, Unit.INSTANCE);
		}

		static <A> Either<List<Unit>, A> conv(Either<Stream<Unit>, A> e) {
				return e.pm(l -> Either.left(l.collect(Collectors.toList())),
										r -> Either.right(r));
		}
  
		@Test
		public void isoEUTest() {
				assertEquals(conv(lrl(isoEU()).apply(Either.left(Stream.empty()))),
										 conv(Either.left(Stream.empty())));
				assertEquals(conv(lrl(isoEU()).apply(Either.left(lu()))),
										 conv(Either.left(lu())));
				assertEquals(conv(lrl(isoEU()).apply(Either.right(Unit.INSTANCE))),
										 conv(Either.right(Unit.INSTANCE)));
				assertEquals(conv(rlr(isoEU()).apply(Either.left(Stream.empty()))),
										 conv(Either.left(Stream.empty())));
				assertEquals(conv(rlr(isoEU()).apply(Either.left(lu()))),
										 conv(Either.left(lu())));
				assertEquals(subStL(isoEU()).apply(Either.right(Unit.INSTANCE))
										 .pm(l -> true, r -> false),
										 true);
		}

		@Test
		public void isoEitherTest() {
				assertEquals(Either.left(false),
										 subStL(isoEither(isoBoolNot(), tISO))
										 .apply(Either.left(true)));
				assertEquals(Either.left(true),
										 subStL(isoEither(isoBoolNot(), tISO))
										 .apply(Either.left(false)));
				assertEquals(Either.right(MEOW),
										 subStL(isoEither(isoBoolNot(), tISO))
										 .apply(Either.right(true)));
		}

		@Test
		public void isoSymmTest() {
				assertEquals(MOE, 
										 subStR(subStR(isoSymm()).apply((ISO) tISO)).apply(false));
		}
}
