import java.util.*
import java.util.stream.Collectors.toList
import java.util.stream.Stream
import java.util.stream.Stream.*


/*
 * so, when are two type, `a` and `b`, considered equal?
 * a definition might be, it is possible to go from `a` to `b`,
 * and from `b` to `a`.
 * Going a roundway trip should leave you the same value.
 * Unfortunately it is virtually impossible to test this in Haskell.
 * This is called ISO.
 * <p>
 * ISO can also be simulated in Java.
 * <p>
 * Created by ice1000 on 17-6-19.
 */
abstract class ISO<A, B> {
	/** go backward */
	abstract fun bw(b: B): A

	/** go forward */
	abstract fun fw(a: A): B
}

abstract class Either<out L, out R> {
	abstract fun <T> pm(lt: (L) -> T, rt: (R) -> T): T
}

fun <L, R> left(l: L): Either<L, R> = object : Either<L, R>() {
	override fun <T> pm(lt: (L) -> T, rt: (R) -> T): T = lt(l)
	override fun equals(other: Any?) = (other as Either<*, *>).pm({ l == it }, { false })
	override fun toString() = "left: $l"
}

fun <L, R> right(r: R): Either<L, R> = object : Either<L, R>() {
	override fun <T> pm(lt: (L) -> T, rt: (R) -> T): T = rt(r)
	override fun equals(other: Any?) = (other as Either<*, *>).pm({ false }, { r == it })
	override fun toString() = "right: $r"
}

private fun <T> Nothing.absurd(): T = this

private inline fun <A, B> iso(crossinline forward: (A) -> B, crossinline backward: (B) -> A): ISO<A, B> = object : ISO<A, B>() {
	override fun bw(b: B): A = backward(b)
	override fun fw(a: A): B = forward(a)
}

/* given ISO a b, we can go from a to b */
fun <A, B> subStL(iso: ISO<A, B>): (A) -> B = iso::fw

/* and vise versa */
fun <A, B> subStR(iso: ISO<A, B>): (B) -> A = iso::bw

/* There can be more than one ISO a b */
fun isoBool(): ISO<Boolean, Boolean> = refl()

fun isoBoolNot(): ISO<Boolean, Boolean> = iso(Boolean::not, Boolean::not)

/* isomorphism is reflexive */
fun <A> refl(): ISO<A, A> = iso({ it }, { it })

/* isomorphism is symmetric */
fun <A, B> symm(iso: ISO<B, A>): ISO<A, B> = iso(iso::bw, iso::fw)

/* isomorphism is transitive */
fun <A, B, C> trans(ab: ISO<A, B>, bc: ISO<B, C>): ISO<A, C> = iso({ bc.fw(ab.fw(it)) }, { ab.bw(bc.bw(it)) })

/* We can combine isomorphism */
fun <A, B, C, D> isoPair(ab: ISO<A, B>, cd: ISO<C, D>): ISO<Pair<A, C>, Pair<B, D>> =
		iso({ (a, c) -> ab.fw(a) to cd.fw(c) }, { (b, d) -> ab.bw(b) to cd.bw(d) })

fun <A, B> isoStream(iso: ISO<A, B>): ISO<Stream<A>, Stream<B>> = iso({ it.map(iso::fw) }, { it.map(iso::bw) })
fun <A, B> isoOptional(iso: ISO<A, B>): ISO<Optional<A>, Optional<B>> = iso({ it.map(iso::fw) }, { it.map(iso::bw) })

fun <A, B, C, D> isoEither(ab: ISO<A, B>, cd: ISO<C, D>): ISO<Either<A, C>, Either<B, D>> =
		iso({ it.pm({ left(ab.fw(it)) }, { right(cd.fw(it)) }) }, { it.pm({ left(ab.bw(it)) }, { right(cd.bw(it)) }) })

/*
* Going another way is hard (and is generally impossible)
* Remember, for all valid ISO, converting and converting back
* is the same as the original value.
* You need this to prove some case are impossible.
*/
fun <A, B> isoUnOptional(iso: ISO<Optional<A>, Optional<B>>): ISO<A, B> = iso({ iso.fw(Optional.of(it)).orElseGet { iso.fw(Optional.empty()).get() } },
		{ iso.bw(Optional.of(it)).orElseGet { iso.bw(Optional.empty()).get() } })

// We cannot have
// isoUnEither ::
// ISO (Either a b) (Either c d) -> ISO a c -> ISO b d.
// Note that we have
fun isoEU(): ISO<Either<Stream<Unit>, Unit>, Either<Stream<Unit>, Nothing>> = iso({ it.pm({ left(concat(of(Unit), it)) }, { left(empty()) }) },
		{ it.pm({ it.collect(toList()).let { if (it.isEmpty()) right(Unit) else left(generate { Unit }.limit(it.size - 1L)) } }, { it.absurd() }) })

// where (), the empty Pair, has 1 value, and Void has 0 value
// If we have isoUnEither,
// We have ISO () Void by calling isoUnEither isoEU
// That is impossible, since we can get a Void by
// substL on ISO () Void
// So it is impossible to have isoUnEither

fun <A, B, C, D> isoFunc(ab: ISO<A, B>, cd: ISO<C, D>): ISO<(A) -> C, (B) -> D> =
		iso({ ac -> { cd.fw(ac(ab.bw(it))) } }, { bd -> { cd.bw(bd(ab.fw(it))) } })

/* And we have isomorphism on isomorphism! */
fun <A, B> isoSymm(): ISO<ISO<A, B>, ISO<B, A>> = iso(::symm, ::symm)

// -------------------------------

/** a = b -> c = d -> a * c = b * d  */
fun <A, B, C, D> isoProd(ab: ISO<A, B>, cd: ISO<C, D>): ISO<Pair<A, C>, Pair<B, D>> = isoPair(ab, cd)

/** a = b -> c = d -> a + c = b + d  */
fun <A, B, C, D> isoPlus(ab: ISO<A, B>, cd: ISO<C, D>): ISO<Either<A, C>, Either<B, D>> = isoEither(ab, cd)

/** a = b -> S a = S b  */
fun <A, B> isoS(iso: ISO<A, B>): ISO<Optional<A>, Optional<B>> = isoOptional(iso)

/** a = b -> c = d -> c ^ a = d ^ b  */
fun <A, B, C, D> isoPow(ab: ISO<A, B>, cd: ISO<C, D>): ISO<(A) -> C, (B) -> D> = isoFunc(ab, cd)

/** a + b = b + a  */
fun <A, B> plusComm(): ISO<Either<A, B>, Either<B, A>> =
		iso({ it.pm({ right(it) }, { left(it) }) }, { it.pm({ right(it) }, { left(it) }) })

/** a + b + c = a + (b + c) */
fun <A, B, C> plusAssoc(): ISO<Either<Either<A, B>, C>, Either<A, Either<B, C>>> =
		iso({ abc -> abc.pm({ ab -> ab.pm(::left, { b -> right(left(b)) }) }) { c -> right(right(c)) } }, { abc -> abc.pm({ a -> left(left(a)) }) { bc -> bc.pm({ b -> left(right(b)) }, ::right) } })

/** a * b = b * a  */
fun <A, B> multComm(): ISO<Pair<A, B>, Pair<B, A>> = iso({ (a, b) -> b to a }, { (b, a) -> a to b })

/** a * b * c = a * (b * c)  */
fun <A, B, C> multAssoc(): ISO<Pair<Pair<A, B>, C>, Pair<A, Pair<B, C>>> =
		iso({ (pair, c) -> Pair(pair.first, pair.second to c) }, { (a, pair) -> Pair(a to pair.first, pair.second) })

/** a * (b + c) = a * b + a * c */
fun <A, B, C> dist(): ISO<Pair<A, Either<B, C>>, Either<Pair<A, B>, Pair<A, C>>> =
		iso({ (a, e) -> e.pm({ b -> left(a to b) }, { c -> right(a to c) }) }, { e -> e.pm({ (a, b) -> a to left(b) }, { (a, c) -> a to right(c) }) })

/** (c ^ b) ^ a = c ^ (a * b)  */
fun <A, B, C> curryISO(): ISO<(A) -> (B) -> C, (Pair<A, B>) -> C> =
		iso({ a -> { (a, b) -> a(a)(b) } }) { ab -> { a -> { b -> ab(a to b) } } }

/**
 * 1 = S O (we are using peano arithmetic)
 * https://en.wikipedia.org/wiki/Peano_axioms
 */
fun one(): ISO<Unit, Optional<Nothing>> = iso({ Optional.empty() }, { Unit })

/** 2 = S (S O)  */
fun two(): ISO<Boolean, Optional<Optional<Void>>> =
		iso({ b -> if (b) Optional.of(Optional.empty()) else Optional.empty() }, { it.isPresent })

/** 0 + b = b  */
fun <B> plusO(): ISO<Either<Nothing, B>, B> =
		iso({ a -> a.pm({ it.absurd() }, { b -> b }) }, ::right)

/* S a + b = S (a + b) */
fun <A, B> plusS(): ISO<Either<Optional<A>, B>, Optional<Either<A, B>>> =
		iso({ oab -> oab.pm({ oa -> oa.map { a -> Optional.of(left<A, B>(a)) }.orElseGet { Optional.empty() } }) { b -> Optional.of(right(b)) } }, { oab ->
			oab.map { ab -> ab.pm({ a -> left<Optional<A>, B>(Optional.of(a)) }, ::right) }.orElseGet { left(Optional.empty()) }
		})

/* 1 + b = S b */
fun <B> plusSO(): ISO<Either<Unit, B>, Optional<B>> = trans(isoPlus(one(), refl<B>()), trans(plusS(), isoS(plusO<B>())))

/** 0 * a = 0  */
fun <A> multO(): ISO<Pair<Nothing, A>, Nothing> = iso({ (no) -> no }) { a -> a.absurd() }

/* S a * b = b + a * b */
fun <A, B> multS(): ISO<Pair<Optional<A>, B>, Either<B, Pair<A, B>>> =
		iso({ (o, b) -> o.map({ a -> right<B, Pair<A, B>>(a to b) }).orElseGet({ left(b) }) }, { bab -> bab.pm({ b -> Pair(Optional.empty(), b) }, { (a, b) -> Pair(Optional.of(a), b) }) })

/** S a * b = b + a * b  */
fun <B> multSO(): ISO<Pair<Unit, B>, B> =
		trans(isoProd(one(), refl<B>()), trans(multS(), trans(isoPlus(refl<B>(), multO<B>()), trans(plusComm(), plusO()))))

/** a ^ 0 = 1  */
fun <A> powO(): ISO<(Nothing) -> A, Unit> = iso({ Unit }, { { no: Nothing -> no.absurd() } })

/** a ^ (S b) = a * (a ^ b)  */
fun <A, B> powS(): ISO<(Optional<B>) -> A, Pair<A, (B) -> A>> =
		iso({ f -> Pair(f(Optional.empty()), { o -> f(Optional.of(o)) }) }, { (a, b) -> { p -> p.map(b).orElseGet({ a }) } })

/**
 * a ^ 1 = a
 * Go the hard way (like multSO, plusSO)
 * to prove that you really get what is going on!
 */
fun <A> powSO(): ISO<(Unit) -> A, A> = iso({ f -> f(Unit) }, { a -> { a } })