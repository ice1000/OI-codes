package codewars;

import org.junit.Test;

import java.lang.reflect.Constructor;
import java.util.Arrays;
import java.util.Optional;
import java.util.function.Function;

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

	private static final String MEOW = "meow";
	private static final String MOE = "moe";

	private static ISO<Boolean, String> tISO = iso(it -> it ? MEOW : MOE, MEOW::equals);

	private static <A, B> Function<A, A> lrl(ISO<A, B> iso) {
		return it -> iso.bw(iso.fw(it));
	}

	private static <A, B> Function<B, B> rlr(ISO<A, B> iso) {
		return it -> iso.fw(iso.bw(it));
	}

	private static String cul(Object a, Object b) {
		return a + " " + b;
	}

	private static String cur(Tuple<?, ?> a) {
		return a.a + " " + a.b;
	}

	private static ISO<Either<Either<Integer, Boolean>, String>, Either<Integer, Either<Boolean, String>>> pa() {
		return plusAssoc();
	}

	private static ISO<Tuple<Tuple<Integer, Boolean>, String>, Tuple<Integer, Tuple<Boolean, String>>> ma() {
		return multAssoc();
	}

	private static ISO<Tuple<Integer, Either<Boolean, String>>, Either<Tuple<Integer, Boolean>, Tuple<Integer, String>>> di() {
		return dist();
	}

	private static ISO<Function<Integer, Function<Boolean, String>>, Function<Tuple<Integer, Boolean>, String>> cu() {
		return curryISO();
	}

	private static final String str = "it was me, DIO!";

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
	public void isoSymmTest() {
		assertEquals(MOE, subStR(subStR(isoSymm()).apply((ISO) tISO)).apply(false));
	}

	@Test
	public void isoStreamTest() {
		assertEquals(Optional.of(MEOW + MEOW + MOE),
				subStL(isoStream(tISO)).apply(Arrays.stream(new Boolean[]{true, true, false})).reduce((a, b) -> a + b));
	}

	@Test
	public void isoFuncTest() {
		assertEquals(MEOW, subStL(isoFunc(symm(tISO), tISO)).apply(MEOW::equals).apply(true));
	}

	@Test
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

	private static <B> ISO<Tuple<Unit, B>, B> multSO_() {
		return trans(isoProd(one(), refl()), trans(multS(), trans(isoPlus(refl(), multO()), trans(plusComm(), plusO()))));
	}

	private static <B> ISO<Either<Unit, B>, Optional<B>> plusSO_() {
		return trans(isoPlus(one(), refl()), trans(plusS(), isoS(plusO())));
	}

	private static ISO<Either<Optional<String>, Integer>, Optional<Either<String, Integer>>> pss() {
		return plusS();
	}

	private static ISO<Either<Unit, Integer>, Optional<Integer>> pso() {
		return plusSO_();
	}

	private static ISO<Tuple<Optional<String>, Integer>, Either<Integer, Tuple<String, Integer>>> mss() {
		return multS();
	}

	private static ISO<Tuple<Unit, Boolean>, Boolean> mso() {
		return multSO_();
	}

	private static ISO<Function<Optional<Integer>, String>, Tuple<String, Function<Integer, String>>> poss() {
		return powS();
	}

	private static <A> ISO<Function<Unit, A>, A> powSO_() {
		return trans(isoPow(one(), refl()), trans(powS(), trans(isoProd(refl(), powO()), trans(multComm(), (ISO) multSO()))));
	}

	/* master spark! */
	private static String func(Integer integer) {
		String[] strings = new String[integer];
		Arrays.fill(strings, "DA★ZE");
		return String.join("|", strings);
	}

	private static String mfunc(Optional<Integer> optional) {
		return optional.map(ISOTest::func).orElse(str);
	}

	private static ISO<Function<Unit, String>, String> poso() {
		return powSO();
	}

	private static <A> ISO<Function<Unit, A>, A> poso_() {
		return powSO_();
	}

	@Test
	public void assoc() {
		assertEquals(Either.left(Either.left(233)), lrl(pa()).apply(Either.left(Either.left(233))));
		assertEquals(Either.left(Either.right(true)), lrl(pa()).apply(Either.left(Either.right(true))));
		assertEquals(Either.right(str), lrl(pa()).apply(Either.right(str)));
		assertEquals(Either.left(233), rlr(pa()).apply(Either.left(233)));
		assertEquals(Either.right(Either.left(true)), rlr(pa()).apply(Either.right(Either.left(true))));
		assertEquals(Either.right(Either.right(str)), rlr(pa()).apply(Either.right(Either.right(str))));
	}

	@Test
	public void distTest() {
		Tuple<Integer, Either<Boolean, String>> tuple = new Tuple<>(0, Either.left(true));
		assertEquals(tuple, lrl(di()).apply(tuple));
		Tuple<Integer, Either<Boolean, String>> tuple2 = new Tuple<>(0, Either.right(str));
		assertEquals(tuple2, lrl(di()).apply(tuple2));
		Either<Tuple<Integer, Boolean>, Tuple<Integer, String>> either = Either.left(new Tuple<>(0, true));
		assertEquals(either, rlr(di()).apply(either));
		Either<Tuple<Integer, Boolean>, Tuple<Integer, String>> either2 = Either.right(new Tuple<>(0, str));
		assertEquals(either2, rlr(di()).apply(either2));
	}

	@Test
	public void curryTest() {
		assertEquals(cul(0, true), lrl(cu()).apply(a -> b -> cul(a, b)).apply(0).apply(true));
		assertEquals(cul(0, true), rlr(cu()).apply(ISOTest::cur).apply(new Tuple<>(0, true)));
	}

	@Test
	public void oneTest() {
		assertEquals(Unit.INSTANCE, lrl(one()).apply(Unit.INSTANCE));
		assertEquals(Optional.empty(), rlr(one()).apply(Optional.empty()));
	}

	@Test
	public void twoTest() {
		assertTrue(lrl(two()).apply(true));
		assertFalse(lrl(two()).apply(false));
		assertEquals(Optional.empty(), rlr(two()).apply(Optional.empty()));
		assertEquals(Optional.of(Optional.empty()), rlr(two()).apply(Optional.of(Optional.empty())));
	}

	@Test
	public void plusTest() {
		assertEquals(Either.right(str), lrl(plusO()).apply(Either.right(str)));
		assertEquals(str, rlr(plusO()).apply(str));
		assertEquals(Either.left(Optional.of(str)), lrl(pss()).apply(Either.left(Optional.of(str))));
		assertEquals(Either.left(Optional.empty()), lrl(pss()).apply(Either.left(Optional.empty())));
		assertEquals(Either.right(233), lrl(pss()).apply(Either.right(233)));
		assertEquals(Optional.of(Either.left(str)), rlr(pss()).apply(Optional.of(Either.left(str))));
		assertEquals(Optional.of(Either.right(233)), rlr(pss()).apply(Optional.of(Either.right(233))));
		assertEquals(Optional.empty(), rlr(pss()).apply(Optional.empty()));
		assertEquals(Either.left(Unit.INSTANCE), lrl(pso()).apply(Either.left(Unit.INSTANCE)));
		assertEquals(Either.right(233), lrl(pso()).apply(Either.right(233)));
		assertEquals(Optional.empty(), rlr(pso()).apply(Optional.empty()));
		assertEquals(Optional.of(233), rlr(pso()).apply(Optional.of(233)));
	}

	@Test
	public void multTest() {
		assertEquals(new Tuple<>(Optional.of(str), 233), lrl(mss()).apply(new Tuple<>(Optional.of(str), 233)));
		assertEquals(new Tuple<>(Optional.empty(), 233), lrl(mss()).apply(new Tuple<>(Optional.empty(), 233)));
		assertEquals(Either.left(233), rlr(mss()).apply(Either.left(233)));
		assertEquals(Either.right(new Tuple<>(str, 233)), rlr(mss()).apply(Either.right(new Tuple<>(str, 233))));
		assertEquals(new Tuple<>(Unit.INSTANCE, true), lrl(mso()).apply((new Tuple<>(Unit.INSTANCE, true))));
		assertEquals(new Tuple<>(Unit.INSTANCE, false), lrl(mso()).apply((new Tuple<>(Unit.INSTANCE, false))));
		assertTrue(rlr(mso()).apply(true));
		assertFalse(rlr(mso()).apply(false));
	}

	@Test
	public void powTest() {
		assertEquals(Unit.INSTANCE, rlr(powO()).apply(Unit.INSTANCE));
		assertEquals("DA★ZE|DA★ZE|DA★ZE", lrl(poss()).apply(ISOTest::mfunc).apply(Optional.of(3)));
		assertEquals(str, lrl(poss()).apply(ISOTest::mfunc).apply(Optional.empty()));
		assertEquals(str, rlr(poss()).apply(new Tuple<>(str, ISOTest::func)).a);
		assertEquals("DA★ZE|DA★ZE|DA★ZE", rlr(poss()).apply(new Tuple<>(str, ISOTest::func)).b.apply(3));
		assertEquals(str, lrl(poso()).apply(unit -> str).apply(Unit.INSTANCE));
		assertEquals(str, rlr(poso()).apply(str));
		assertEquals(str, lrl(poso_()).apply(unit -> str).apply(Unit.INSTANCE));
		assertEquals(str, rlr(poso_()).apply(str));
	}

	@Test
	public void privateConstructors() {
		for (Constructor<?> constructor : Unit.class.getConstructors()) assertFalse(constructor.isAccessible());
		for (Constructor<?> constructor : Either.class.getConstructors()) assertFalse(constructor.isAccessible());
		for (Constructor<?> constructor : codewars.ISO.Void.class.getConstructors()) assertFalse(constructor.isAccessible());
	}

	@Test
	public void shouldntHackByChangingEquals() {
		assertNotEquals(new Tuple<>(Unit.INSTANCE, true), lrl(mso()).apply((new Tuple<>(Unit.INSTANCE, false))));
		assertNotEquals(Either.right(new Tuple<>(str, 666)), rlr(mss()).apply(Either.right(new Tuple<>(str, 233))));
		assertNotEquals(Either.right(new Tuple<>("str", 233)), rlr(mss()).apply(Either.right(new Tuple<>(str, 233))));
		assertNotEquals(new Tuple<Integer, Either<Boolean, String>>(0, Either.left(false)), lrl(di()).apply(new Tuple<>(0, Either.left(true))));
	}
}
