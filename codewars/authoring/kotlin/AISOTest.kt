import org.junit.Assert.assertEquals
import org.junit.Assert.assertFalse
import org.junit.Test
import java.util.*
import java.util.Arrays.stream
import java.util.Optional.empty
import java.util.Optional.of
import java.util.stream.Collectors
import java.util.stream.Stream
import kotlin.test.*


class ISOTest {

	@Test
	fun subStLTest() {
		assertEquals(MEOW, subStL(tISO)(true))
		assertEquals(false, subStL(isoBool())(false))
		assertEquals(true, subStL(isoBool())(true))
	}

	@Test
	fun subStRTest() {
		assertEquals(MEOW, subStL(subStR(iso({ _: ISO<Boolean, String> -> Any() }, { _: Any -> tISO }))(Any()))(true))
		assertEquals(true, subStR(isoBool())(true))
		assertEquals(false, subStR(isoBool())(false))
	}

	@Test
	fun reflTest() = assertEquals(MEOW, subStL(subStL(refl<ISO<Boolean, String>>())(tISO))(true))

	@Test
	fun symmTest() = assertEquals(MEOW, subStR(symm(tISO))(true))

	@Test
	fun transTest() = assertEquals(MEOW, subStL(trans(refl(), trans(tISO, refl())))(true))

	@Test
	fun isoPairTest() = assertEquals(MEOW to MOE, subStL(isoPair(tISO, tISO))(Pair(true, false)))

	@Test
	fun isoStreamTest() = assertEquals(of(MEOW + MEOW + MOE), subStL(isoStream(tISO))(stream(arrayOf(true, true, false))).reduce(String::plus))

	@Test
	fun isoFuncTest() = assertEquals(MEOW, subStL(isoFunc(symm(tISO), tISO))(MEOW::equals)(true))

	@Test
	fun isoSymmTest() = assertEquals(MOE, subStR(subStR(isoSymm<String, Boolean>())(tISO))(false))

	@Test
	fun isoOptionalTest() {
		assertFalse(subStL(isoOptional(tISO))(empty()).isPresent)
		assertEquals(MEOW, subStL(isoOptional(tISO))(of(true)).get())
	}

	@Test
	fun isoUnOptionalTest() {
		assertEquals(false, subStL(bISO)(true))
		assertEquals(true, subStL(bISO)(false))
		assertEquals(false, subStL(badISO)(true))
		assertFailsWith<NoSuchElementException> { subStL(badISO)(false) }
		val bi = isoUnOptional(isoOptional(refl<Any>()))
		assertEquals(true, lrl(bi)(true))
		assertEquals(false, lrl(bi)(false))
		assertEquals(true, rlr(bi)(true))
		assertEquals(false, rlr(bi)(false))
		val biso = symm(isoUnOptional(symm(mISO)))
		assertEquals(false, subStL(bISO)(true))
		assertEquals(true, subStL(bISO)(false))
		assertEquals(false, subStL(badISO)(true))
		assertFailsWith<NoSuchElementException> { subStL(badISO)(false) }
	}

	private fun lu(): Stream<Unit> = Stream.of(Unit, Unit, Unit, Unit, Unit, Unit, Unit, Unit)

	@Test
	fun isoEUTest() {
		assertEquals(conv(lrl(isoEU())(left(Stream.empty<Unit>()))), conv(left<Stream<Unit>, Nothing>(Stream.empty())))
		assertEquals(conv(lrl(isoEU())(left(lu()))), conv(left<Stream<Unit>, Nothing>(lu())))
		assertEquals(conv(lrl(isoEU())(right(Unit))), conv(right(Unit)))
		assertEquals(conv(rlr(isoEU())(left(Stream.empty<Unit>()))), conv(left<Stream<Unit>, Nothing>(Stream.empty())))
		assertEquals(conv(rlr(isoEU())(left(lu()))), conv(left<Stream<Unit>, Nothing>(lu())))
		assertEquals(subStL(isoEU())(right(Unit)).pm({ true }, { false }), true)
	}

	@Test
	fun isoEitherTest() {
		assertEquals(left<Boolean, Nothing>(false), subStL(isoEither(isoBoolNot(), tISO))(left(true)))
		assertEquals(left<Boolean, Nothing>(true), subStL(isoEither(isoBoolNot(), tISO))(left(false)))
		assertEquals(right<Boolean, String>(MEOW), subStL(isoEither(isoBoolNot(), tISO))(right(true)))
	}

	@Test
	fun assoc() {
		assertEquals(left<Either<Int, Boolean>, String>(left(233)), lrl(pa())(left(left(233))))
		assertEquals(left<Either<Int, Boolean>, String>(right(true)), lrl(pa())(left(right(true))))
		assertEquals(right<Either<Int, Boolean>, String>(str), lrl(pa())(right(str)))
		assertEquals(left<Int, Either<Boolean, String>>(233), rlr(pa())(left(233)))
		assertEquals(right<Int, Either<Boolean, String>>(left(true)), rlr(pa())(right(left(true))))
		assertEquals(right<Int, Either<Boolean, String>>(right(str)), rlr(pa())(right(right(str))))
	}

	@Test
	fun distTest() {
		val tuple = Pair(0, left<Boolean, String>(true))
		assertEquals(tuple, lrl(di())(tuple))
		val tuple2 = Pair(0, right<Boolean, String>(str))
		assertEquals(tuple2, lrl(di())(tuple2))
		val either = left<Pair<Int, Boolean>, Pair<Int, String>>(Pair(0, true))
		assertEquals(either, rlr(di())(either))
		val either2 = right<Pair<Int, Boolean>, Pair<Int, String>>(Pair(0, str))
		assertEquals(either2, rlr(di())(either2))
	}

	@Test
	fun curryTest() {
		assertEquals(cul(0, true), lrl(cu())({ a -> { b -> cul(a, b) } })(0)(true))
		assertEquals(cul(0, true), rlr(cu())(CO::cur)(Pair(0, true)))
	}

	@Test
	fun oneTest() {
		assertEquals(Unit, lrl(one())(Unit))
		assertEquals(Optional.empty<Optional<Unit>>(), rlr(one())(Optional.empty()))
	}

	@Test
	fun twoTest() {
		assertTrue(lrl(two())(true))
		assertFalse(lrl(two())(false))
		assertEquals(Optional.empty<Optional<Unit>>(), rlr(two())(Optional.empty()))
		assertEquals(Optional.of<Optional<Unit>>(Optional.empty()), rlr(two())(Optional.of(Optional.empty())))
	}

	@Test
	fun plusTest() {
		assertEquals(right<Boolean, String>(str), lrl(plusO<String>())(right(str)))
		assertEquals(str, rlr(plusO<String>())(str))
		assertEquals(left<Optional<String>, Nothing>(Optional.of(str)), lrl(pss())(left(Optional.of(str))))
		assertEquals(left<Optional<String>, Nothing>(Optional.empty()), lrl(pss())(left(Optional.empty())))
		assertEquals(right<Optional<String>, Int>(233), lrl(pss())(right(233)))
		assertEquals(Optional.of(left<String, Int>(str)), rlr(pss())(Optional.of(left(str))))
		assertEquals(Optional.of(right<String, Int>(233)), rlr(pss())(Optional.of(right(233))))
		assertEquals(Optional.empty<Nothing>(), rlr(pss())(Optional.empty()))
		assertEquals(left<Unit, Int>(Unit), lrl(pso())(left(Unit)))
		assertEquals(right<Unit, Int>(233), lrl(pso())(right(233)))
		assertEquals(Optional.empty<Nothing>(), rlr(pso())(Optional.empty()))
		assertEquals(Optional.of(233), rlr(pso())(Optional.of(233)))
	}

	@Test
	fun multTest() {
		assertEquals(Optional.of(str) to 233, lrl(mss())(Optional.of(str) to 233))
		assertEquals(Optional.empty<String>() to 233, lrl(mss())(Optional.empty<String>() to 233))
		assertEquals(left<Int, Pair<String, Int>>(233), rlr(mss())(left(233)))
		assertEquals(right<Int, Pair<String, Int>>(str to 233), rlr(mss())(right(str to 233)))
		assertEquals(Unit to true, lrl(mso())(Unit to true))
		assertEquals(Unit to false, lrl(mso())(Unit to false))
		assertTrue(rlr(mso())(true))
		assertFalse(rlr(mso())(false))
	}

	@Test
	fun powTest() {
		assertEquals(Unit, rlr(powO<Nothing>())(Unit))
		assertEquals("DA★ZE|DA★ZE|DA★ZE", lrl(poss())(CO::mfunc)(Optional.of(3)))
		assertEquals(str, lrl(poss())(CO::mfunc)(Optional.empty()))
		assertEquals(str, rlr(poss())(Pair(str, CO::func)).first)
		assertEquals("DA★ZE|DA★ZE|DA★ZE", rlr(poss())(Pair(str, CO::func)).second(3))
		assertEquals(str, lrl(poso())({ str })(Unit))
		assertEquals(str, rlr(poso())(str))
		assertEquals(str, lrl(poso_())({ str })(Unit))
		assertEquals(str, rlr(poso_())(str))
	}

	@Test
	fun shouldntHackByChangingEquals() {
		assertNotEquals(right(Pair(str, 666)), rlr(mss())(right(Pair(str, 233))))
		assertNotEquals(right(Pair("str", 233)), rlr(mss())(right(Pair(str, 233))))
	}

	companion object CO {
		private inline fun <A, B> iso(crossinline forward: (A) -> B, crossinline backward: (B) -> A): ISO<A, B> = object : ISO<A, B>() {
			override fun bw(b: B): A = backward(b)
			override fun fw(a: A): B = forward(a)
		}

		private fun cul(a: Any, b: Any): String = "$a $b"
		private fun cur(a: Pair<Any, Any>): String = "${a.first} ${a.second}"
		private fun pa(): ISO<Either<Either<Int, Boolean>, String>, Either<Int, Either<Boolean, String>>> = plusAssoc()
		private fun ma(): ISO<Pair<Pair<Int, Boolean>, String>, Pair<Int, Pair<Boolean, String>>> = multAssoc()
		private fun di(): ISO<Pair<Int, Either<Boolean, String>>, Either<Pair<Int, Boolean>, Pair<Int, String>>> = dist()
		private fun cu(): ISO<(Int) -> (Boolean) -> String, (Pair<Int, Boolean>) -> String> = curryISO()
		private fun <B> plusSO_(): ISO<Either<Unit, B>, Optional<B>> = trans(isoPlus(one(), refl<B>()), trans(plusS(), isoS(plusO<B>())))
		private fun <B> multSO_(): ISO<Pair<Unit, B>, B> = trans(isoProd(one(), refl<B>()), trans(multS(), trans(isoPlus(refl<B>(), multO<B>()), trans(plusComm(), plusO()))))
		private fun mfunc(optional: Optional<Int>): String = optional.map(CO::func).orElse(str)
		private fun pso(): ISO<Either<Unit, Int>, Optional<Int>> = plusSO_()
		private fun mss(): ISO<Pair<Optional<String>, Int>, Either<Int, Pair<String, Int>>> = multS()
		private fun mso(): ISO<Pair<Unit, Boolean>, Boolean> = multSO_()
		private fun poss(): ISO<(Optional<Int>) -> String, Pair<String, (Int) -> String>> = powS()
		private fun pss(): ISO<Either<Optional<String>, Int>, Optional<Either<String, Int>>> = plusS()
		private fun poso(): ISO<(Unit) -> String, String> = powSO()
		private fun poso_(): ISO<(Unit) -> String, String> = powSO_()
		private fun <A> powSO_(): ISO<(Unit) -> A, A> =
				trans(isoPow(one(), refl<A>()), trans(powS(), trans(isoProd(refl<A>(), powO<A>()), trans(multComm(), multSO()))))

		/** master spark! */
		private fun func(integer: Int): String {
			val strings = arrayOfNulls<String>(integer)
			Arrays.fill(strings, "DA★ZE")
			return strings.joinToString("|")
		}

		private val MEOW = "meow"
		private val MOE = "moe"
		private val tISO = iso({ it: Boolean -> if (it) MEOW else MOE }, { it: String -> MEOW == it })
		private val mISO = iso<Optional<Boolean>, Optional<Boolean>>({ it.map({ if (it) of(false) else empty() }).orElseGet({ of(true) }) }, { it })
		private val bISO = isoUnOptional(mISO)
		private val badMISO = iso<Optional<Boolean>, Optional<Boolean>>({ it.flatMap({ if (it) of(false) else empty() }) }, { it })
		private val badISO = isoUnOptional(badMISO)
		private fun <A, B> lrl(iso: ISO<A, B>): (A) -> A = { iso.bw(iso.fw(it)) }
		private fun <A, B> rlr(iso: ISO<A, B>): (B) -> B = { iso.fw(iso.bw(it)) }
		private val str = "it was me, DIO!"
		private val lu = stream(arrayOf(0, 1, 2, 3, 4, 5, 6, 7))
		internal fun <A> conv(e: Either<Stream<Unit>, A>): Either<List<Unit>, A> = e.pm({ left(it.collect(Collectors.toList())) }, ::right)
	}
}