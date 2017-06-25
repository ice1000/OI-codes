package codewars;

import java.lang.annotation.ElementType;
import java.lang.annotation.Target;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

/**
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

	/*
	 * Please copy your code of Isomorphism to here.
	 *
   * Sometimes, we can treat a Type as a Number:
   * if a Type t has n distinct value, it's Number is n.
   * This is formally called cardinality.
   * See https://en.wikipedia.org/wiki/Cardinality
   *
   * Void has cardinality of 0 (we will abreviate it Void is 0).
   * () is 1.
   * Bool is 2.
   * Maybe a is 1 + a.
   * We will be using peano arithmetic so we will write it as S a.
   * https://en.wikipedia.org/wiki/Peano_axioms
   * Either a b is a + b.
   * (a, b) is a * b.
   * a -> b is b ^ a. Try counting (() -> Bool) and (Bool -> ())
   *
   * Algebraic data type got the name because
   * it satisfies a lot of algebraic rules under isomorphism
	 */

	/** go backward */
	abstract A bw(final B b);

	/** go forward */
	abstract B fw(final A a);

	@Target({ElementType.METHOD, ElementType.CONSTRUCTOR, ElementType.FIELD})
	@interface Helper {
		String whenSubmit();
	}

	/**
	 * Either in Haskell
	 *
	 * @param <L> left
	 * @param <R> right
	 */
	final static class Either<L, R> {
		final L l;
		final R r;

		private Either(final L l, final R r) {
			if ((null == l) == (null == r))
				throw new IllegalArgumentException("l and r cannot be both null or both non-null");
			this.l = l;
			this.r = r;
		}

		@Helper(whenSubmit = "delete")
		Either<R, L> invert() {
			return new Either<>(r, l);
		}

		static <L, R> Either<L, R> left(final L l) {
			return new Either<>(l, null);
		}

		static <L, R> Either<L, R> right(final R r) {
			return new Either<>(null, r);
		}

		@Helper(whenSubmit = "delete")
		<L2, R2> Either<L2, R2> map(Function<? super L, ? extends L2> lf, Function<? super R, ? extends R2> rf) {
			return new Either<>(null != l ? lf.apply(l) : null, null != r ? rf.apply(r) : null);
		}
	}

	final static class Tuple<A, B> {
		final A a;
		final B b;

		Tuple(final A a, final B b) {
			this.a = a;
			this.b = b;
		}

		@Helper(whenSubmit = "delete")
		Tuple<B, A> invert() {
			return new Tuple<>(b, a);
		}

		@Override
		@SuppressWarnings("unchecked")
		public boolean equals(Object o) {
			if (null == o || !(o instanceof Tuple<?, ?>)) return false;
			Tuple<A, B> tuple = (Tuple<A, B>) o;
			return a == tuple.a && b == tuple.b;
		}
	}

	final static class Unit {
		public static Unit INSTANCE = new Unit();

		private Unit() {
		}
	}

	@Helper(whenSubmit = "delete")
	static <A, B> ISO<A, B> iso(Function<A, B> forward, Function<B, A> backward) {
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

	@Helper(whenSubmit = "delete")
	static <A, B> Function<A, B> subStL(final ISO<A, B> iso) {
		return iso::fw;
	}

	@Helper(whenSubmit = "delete")
	static <A, B> Function<B, A> subStR(final ISO<A, B> iso) {
		return iso::bw;
	}

	@Helper(whenSubmit = "delete")
	static ISO<Boolean, Boolean> isoBool() {
		return refl();
	}

	@Helper(whenSubmit = "delete")
	static ISO<Boolean, Boolean> isoBoolNot() {
		return iso(a -> !a, b -> !b);
	}

	@Helper(whenSubmit = "delete")
	static <A> ISO<A, A> refl() {
		return iso(a -> a, b -> b);
	}

	@Helper(whenSubmit = "delete")
	static <A, B> ISO<A, B> symm(final ISO<B, A> iso) {
		return iso(iso::bw, iso::fw);
	}

	@Helper(whenSubmit = "delete")
	static <A, B, C> ISO<A, C> trans(ISO<A, B> ab, ISO<B, C> bc) {
		return iso(a -> bc.fw(ab.fw(a)), c -> ab.bw(bc.bw(c)));
	}

	@Helper(whenSubmit = "delete")
	static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoTuple(ISO<A, B> ab, ISO<C, D> cd) {
		return iso(ac -> new Tuple<>(ab.fw(ac.a), cd.fw(ac.b)), bd -> new Tuple<>(ab.bw(bd.a), cd.bw(bd.b)));
	}

	@Helper(whenSubmit = "delete")
	static <A, B> ISO<Stream<A>, Stream<B>> isoStream(ISO<A, B> iso) {
		return iso(as -> as.map(iso::fw), bs -> bs.map(iso::bw));
	}

	@Helper(whenSubmit = "delete")
	static <A, B> ISO<Optional<A>, Optional<B>> isoOptional(ISO<A, B> iso) {
		return iso(a -> a.map(iso::fw), b -> b.map(iso::bw));
	}

	@Helper(whenSubmit = "delete")
	static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoEither(ISO<A, B> ab, ISO<C, D> cd) {
		return iso(a -> a.map(ab::fw, cd::fw), b -> b.map(ab::bw, cd::bw));
	}

	@Helper(whenSubmit = "delete")
	@SuppressWarnings("ConstantConditions")
	static <A, B> ISO<A, B> isoUnOptional(ISO<Optional<A>, Optional<B>> iso) {
		return iso(a -> iso.fw(Optional.of(a))
						.orElseGet(() -> iso.fw(Optional.empty()).get()),
				b -> iso.bw(Optional.of(b))
						.orElseGet(() -> iso.bw(Optional.empty()).get()));
	}

	@Helper(whenSubmit = "delete")
	static <A, B, C, D> ISO<Function<A, C>, Function<B, D>> isoFunc(ISO<A, B> ab, ISO<C, D> cd) {
		return iso(ac -> a -> cd.fw(ac.apply(ab.bw(a))), bd -> b -> cd.bw(bd.apply(ab.fw(b))));
	}

	@Helper(whenSubmit = "delete")
	static <A, B> ISO<ISO<A, B>, ISO<B, A>> isoSymm() {
		return iso(ISO::symm, ISO::symm);
	}

	// ---------------------------

	/** a = b -> c = d -> a * c = b * d */
	static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoProd(ISO<A, B> ab, ISO<C, D> cd) {
		return isoTuple(ab, cd);
	}

	/** a = b -> c = d -> a + c = b + d */
	static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoPlus(ISO<A, B> ab, ISO<C, D> cd) {
		return isoEither(ab, cd);
	}

	/** a = b -> S a = S b */
	static <A, B> ISO<Optional<A>, Optional<B>> isoS(ISO<A, B> iso) {
		return isoOptional(iso);
	}

	/** a = b -> c = d -> c ^ a = d ^ b */
	static <A, B, C, D> ISO<Function<A, C>, Function<B, D>> isoPow(ISO<A, B> ab, ISO<C, D> cd) {
		return isoFunc(ab, cd);
	}

	/** a + b = b + a */
	static <A, B> ISO<Either<A, B>, Either<B, A>> plusComm() {
		return iso(Either::invert, Either::invert);
	}

	/** a + b + c = a + (b + c) */
	static <A, B, C> ISO<Either<Either<A, B>, C>, Either<A, Either<B, C>>> plusAssoc() {
		return iso(a -> null != a.l ? null != a.l.l ? Either.left(a.l.l) : Either.right(Either.left(a.l.r)) : Either.right(Either.right(a.r)),
				a -> null != a.l ? Either.left(Either.left(a.l)) : null != a.r.l ? Either.left(Either.right(a.r.l)) : Either.right(a.r.r));
	}

	/** a * b = b * a */
	static <A, B> ISO<Tuple<A, B>, Tuple<B, A>> multComm() {
		return iso(Tuple::invert, Tuple::invert);
	}

	/** a * b * c = a * (b * c) */
	static <A, B, C> ISO<Tuple<Tuple<A, B>, C>, Tuple<A, Tuple<B, C>>> multAssoc() {
		return iso(a -> new Tuple<>(a.a.a, new Tuple<>(a.a.b, a.b)), a -> new Tuple<>(new Tuple<>(a.a, a.b.a), a.b.b));
	}

	/** a * (b + c) = a * b + a * c */
	static <A, B, C> ISO<Tuple<A, Either<B, C>>, Either<Tuple<A, B>, Tuple<A, C>>> dist() {
		return iso(a -> null != a.b.l ? Either.left(new Tuple<>(a.a, a.b.l)) : Either.right(new Tuple<>(a.a, a.b.r)),
				a -> null != a.l ? new Tuple<>(a.l.a, Either.left(a.l.b)) : new Tuple<>(a.r.a, Either.right(a.r.b)));
	}

	/** (c ^ b) ^ a = c ^ (a * b) */
	static <A, B, C> ISO<Function<A, Function<B, C>>, Function<Tuple<A, B>, C>> curryISO() {
		return iso(a -> ab -> a.apply(ab.a).apply(ab.b), ab -> a -> b -> ab.apply(new Tuple<>(a, b)));
	}

	/**
	 * 1 = S O (we are using peano arithmetic)
	 * https://en.wikipedia.org/wiki/Peano_axioms
	 */
	static ISO<Unit, Optional<Void>> one() {
		return iso(ignored -> Optional.empty(), ignored -> Unit.INSTANCE);
	}

	/** 2 = S (S O) */
	static ISO<Boolean, Optional<Optional<Void>>> two() {
		return iso(bool -> bool ? Optional.of(Optional.empty()) : Optional.empty(), Optional::isPresent);
	}

	/** 0 + b = b */
	static <B> ISO<Either<Void, B>, B> plusO() {
		return iso(a -> a.r, Either::right);
	}

	/** S a + b = S (a + b) */
	static <A, B> ISO<Either<Optional<A>, B>, Optional<Either<A, B>>> plusS() {
		return iso(a -> null != a.l ? a.l.map(Either::left) : Optional.of(Either.right(a.r)),
				a -> a.isPresent() ? null != a.get().l ? Either.left(Optional.of(a.get().l)) : Either.right(a.get().r) : Either.left(Optional.empty()));
	}

	/** 1 + b = S b */
	static <B> ISO<Either<Unit, B>, Optional<B>> plusSO() {
		return trans(isoPlus(one(), refl()), trans(plusS(), isoS(plusO())));
	}

	/** 0 * a = 0 */
	static <A> ISO<Tuple<Void, A>, A> multO() {
		return iso(a -> a.b, a -> new Tuple<>(null, a));
	}

	/** S a * b = b + a * b */
	static <A, B> ISO<Tuple<Optional<A>, B>, Either<B, Tuple<A, B>>> multS() {
		return iso(a -> a.a.<Either<B, Tuple<A, B>>>map(a1 -> Either.right(new Tuple<>(a1, a.b))).orElseGet(() -> Either.left(a.b)),
				a -> null != a.l ? new Tuple<>(Optional.empty(), a.l) : new Tuple<>(Optional.of(a.r.a), a.r.b));
	}

	/** S a * b = b + a * b */
	static <B> ISO<Tuple<Unit, B>, B> multSO() {
		// return trans(isoProd(one(), refl()), trans(multS(), trans(isoPlus(refl(), multO()), trans(plusComm(), plusO()))));
		return iso(a -> a.b, b -> new Tuple<>(null, b));
	}

	/** a ^ 0 = 1 */
	static <A> ISO<Function<Void, A>, Unit> powO() {
		return iso(ignored -> Unit.INSTANCE, unit -> v -> null);
	}

	/** a ^ (S b) = a * (a ^ b) */
	static <A, B> ISO<Function<Optional<B>, A>, Tuple<A, Function<B, A>>> powS() {
		return iso(func -> new Tuple<>(func.apply(Optional.empty()), func.compose(Optional::of)),
				tuple -> b -> b.map(tuple.b).orElseGet(() -> tuple.a));
	}

	/**
	 * a ^ 1 = a
	 * Go the hard way (like multSO, plusSO)
	 * to prove that you really get what is going on!
	 */
	static <A> ISO<Function<Unit, A>, A> powSO() {
		return iso(fun -> fun.apply(Unit.INSTANCE), a -> unit -> a);
	}

	/*
	 * Here's a trick:
   * replace undefined with the rhs of the comment on previous line
   * When you're not sure what to fill in for a value,
   * Have it as a _
   * GHC will goes like
   * "Found hole `_' with type: (Num (ISO (() -> a) (Maybe b0 -> a0)))"
   * So you can immediately see value of what type are needed
   * This process can be repeat indefinitely -
   * For example you might replace `_` with `isoFunc _ _`
   * So GHC hint you on more specific type.
   * This is especially usefull if you have complex type.
   * See https://wiki.haskell.org/GHC/Typed_holes
   * And "stepwise refinement" for more details.
   */
}
