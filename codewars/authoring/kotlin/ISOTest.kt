import org.junit.Assert.assertEquals
import org.junit.Assert.assertFalse
import org.junit.Test
import java.util.*
import java.util.Arrays.*
import java.util.Optional.*
import java.util.stream.Collectors
import java.util.stream.Stream
import kotlin.test.assertFailsWith

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

	@Test fun reflTest() = assertEquals(MEOW, subStL(subStL(refl<ISO<Boolean, String>>())(tISO))(true))
	@Test fun symmTest() = assertEquals(MEOW, subStR(symm(tISO))(true))
	@Test fun transTest() = assertEquals(MEOW, subStL(trans(refl(), trans(tISO, refl())))(true))
	@Test fun isoPairTest() = assertEquals(MEOW to MOE, subStL(isoPair(tISO, tISO))(Pair(true, false)))
	@Test fun isoStreamTest() = assertEquals(of(MEOW + MEOW + MOE), subStL(isoStream(tISO))(stream(arrayOf(true, true, false))).reduce(String::plus))
	@Test fun isoFuncTest() = assertEquals(MEOW, subStL(isoFunc(symm(tISO), tISO))(MEOW::equals)(true))
	@Test fun isoSymmTest() = assertEquals(MOE, subStR(subStR(isoSymm<String, Boolean>())(tISO))(false))

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

	companion object {
		private inline fun <A, B> iso(crossinline forward: (A) -> B, crossinline backward: (B) -> A): ISO<A, B> {
			return object : ISO<A, B>() {
				override fun bw(b: B): A = backward(b)
				override fun fw(a: A): B = forward(a)
			}
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