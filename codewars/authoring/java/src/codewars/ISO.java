package codewars;

import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

/* Please copy your code of Isomorphism to here. */
public abstract class ISO<A, B> {
	/* go backward */
	abstract A bw(final B b);

	/* go forward */
	abstract B fw(final A a);

	abstract static class Either<L, R> {
		public abstract <T> T pm(Function<L, T> lt, Function<R, T> rt);

		static <L, R> Either<L, R> left(L l) {
			return new Either<L, R>() {
				@Override
				public <T> T pm(Function<L, T> lt, Function<R, T> rt) {
					return lt.apply(l);
				}

				@Override
				public boolean equals(Object rhs) {
					return rhs instanceof Either<?, ?> && ((Either<?, ?>) rhs).pm(l::equals, rr -> false);
				}
			};
		}

		static <L, R> Either<L, R> right(R r) {
			return new Either<L, R>() {
				@Override
				public <T> T pm(Function<L, T> lt, Function<R, T> rt) {
					return rt.apply(r);
				}

				@Override
				public boolean equals(Object rhs) {
					return rhs instanceof Either<?, ?> && ((Either<?, ?>) rhs).pm(ll -> false, r::equals);
				}
			};
		}
	}

	final static class Tuple<A, B> {
		A a;
		B b;

		Tuple(A a, B b) {
			this.a = a;
			this.b = b;
		}

		@Override
		public boolean equals(Object rhs) {
			Tuple<A, B> ab = (Tuple<A, B>) rhs;
			return a.equals(ab.a) && b.equals(ab.b);
		}
	}

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

	/* given ISO a b, we can go from a to b */
	static <A, B> Function<A, B> subStL(final ISO<A, B> iso) {
		return iso::fw;
	}

	/* and vise versa */
	static <A, B> Function<B, A> subStR(final ISO<A, B> iso) {
		return iso::bw;
	}

	/* There can be more than one ISO a b */
	static ISO<Boolean, Boolean> isoBool() {
		return refl();
	}

	static ISO<Boolean, Boolean> isoBoolNot() {
		return iso(a -> !a, b -> !b);
	}

	/* isomorphism is reflexive */
	static <A> ISO<A, A> refl() {
		return iso(a -> a, b -> b);
	}

	/* isomorphism is symmetric */
	static <A, B> ISO<A, B> symm(final ISO<B, A> iso) {
		return iso(iso::bw, iso::fw);
	}

	/* isomorphism is transitive */
	static <A, B, C> ISO<A, C> trans(final ISO<A, B> ab, final ISO<B, C> bc) {
		return iso(a -> bc.fw(ab.fw(a)), c -> ab.bw(bc.bw(c)));
	}

	/* We can combine isomorphism */
	static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoTuple(final ISO<A, B> ab, final ISO<C, D> cd) {
		return iso(ac -> new Tuple<>(ab.fw(ac.a), cd.fw(ac.b)), bd -> new Tuple<>(ab.bw(bd.a), cd.bw(bd.b)));
	}

	static <A, B> ISO<Stream<A>, Stream<B>> isoStream(final ISO<A, B> iso) {
		return iso(as -> as.map(iso::fw), bs -> bs.map(iso::bw));
	}

	static <A, B> ISO<Optional<A>, Optional<B>> isoOptional(final ISO<A, B> iso) {
		return iso(a -> a.map(iso::fw), b -> b.map(iso::bw));
	}

	static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoEither(final ISO<A, B> ab, final ISO<C, D> cd) {
		return iso(l -> l.pm(a -> Either.left(ab.fw(a)), c -> Either.right(cd.fw(c))),
				r -> r.pm(b -> Either.left(ab.bw(b)), d -> Either.right(cd.bw(d))));
	}

	/*
	 * Going another way is hard (and is generally impossible)
	 * Remember, for all valid ISO, converting and converting back
	 * is the same as the original value.
	 * You need this to prove some case are impossible.
	 */
	static <A, B> ISO<A, B> isoUnOptional(final ISO<Optional<A>, Optional<B>> iso) {
		return iso(a -> iso.fw(Optional.of(a)).orElseGet(() -> iso.fw(Optional.empty()).get()),
				b -> iso.bw(Optional.of(b)).orElseGet(() -> iso.bw(Optional.empty()).get()));
	}

	static <A, B, C, D> ISO<Function<A, C>, Function<B, D>> isoFunc(final ISO<A, B> ab, final ISO<C, D> cd) {
		return iso(ac -> a -> cd.fw(ac.apply(ab.bw(a))), bd -> b -> cd.bw(bd.apply(ab.fw(b))));
	}

	/* And we have isomorphism on isomorphism! */
	static <A, B> ISO<ISO<A, B>, ISO<B, A>> isoSymm() {
		return iso(ISO::symm, ISO::symm);
	}

	final static class Unit {
		public static Unit INSTANCE = new Unit();

		private Unit() {
		}
	}

	interface Void {
		<T> T absurd();
	}

  /*
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

	/* a = b -> c = d -> a * c = b * d */
	static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoProd(ISO<A, B> ab, ISO<C, D> cd) {
		return isoTuple(ab, cd);
	}

	/* a = b -> c = d -> a + c = b + d */
	static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoPlus(ISO<A, B> ab, ISO<C, D> cd) {
		return isoEither(ab, cd);
	}

	/* a = b -> S a = S b */
	static <A, B> ISO<Optional<A>, Optional<B>> isoS(ISO<A, B> iso) {
		return isoOptional(iso);
	}

	/* a = b -> c = d -> c ^ a = d ^ b */
	static <A, B, C, D> ISO<Function<A, C>, Function<B, D>> isoPow(ISO<A, B> ab, ISO<C, D> cd) {
		return isoFunc(ab, cd);
	}

	/* a + b = b + a */
	static <A, B> ISO<Either<A, B>, Either<B, A>> plusComm() {
		return iso(ab -> ab.pm(Either::right, Either::left), ba -> ba.pm(Either::right, Either::left));
	}

	/* a + b + c = a + (b + c) */
	static <A, B, C> ISO<Either<Either<A, B>, C>, Either<A, Either<B, C>>> plusAssoc() {
		return iso(
				abc -> abc.pm(ab -> ab.pm(Either::left, b -> Either.right(Either.left(b))), c -> Either.right(Either.right(c))),
				abc -> abc.pm(a -> Either.left(Either.left(a)), bc -> bc.pm(b -> Either.left(Either.right(b)), Either::right)));
	}

	/* a * b = b * a */
	static <A, B> ISO<Tuple<A, B>, Tuple<B, A>> multComm() {
		return iso(ab -> new Tuple<>(ab.b, ab.a), ba -> new Tuple<>(ba.b, ba.a));
	}

	/* a * b * c = a * (b * c) */
	static <A, B, C> ISO<Tuple<Tuple<A, B>, C>, Tuple<A, Tuple<B, C>>> multAssoc() {
		return iso(
				a -> new Tuple<>(a.a.a, new Tuple<>(a.a.b, a.b)),
				a -> new Tuple<>(new Tuple<>(a.a, a.b.a), a.b.b));
	}

	/* a * (b + c) = a * b + a * c */
	static <A, B, C> ISO<Tuple<A, Either<B, C>>, Either<Tuple<A, B>, Tuple<A, C>>> dist() {
		return iso(
				abc -> abc.b.pm(b -> Either.left(new Tuple<>(abc.a, b)), c -> Either.right(new Tuple<>(abc.a, c))),
				abac -> abac.pm(ab -> new Tuple<>(ab.a, Either.left(ab.b)), ac -> new Tuple<>(ac.a, Either.right(ac.b))));
	}

	/* (c ^ b) ^ a = c ^ (a * b) */
	static <A, B, C> ISO<Function<A, Function<B, C>>, Function<Tuple<A, B>, C>> curryISO() {
		return iso(a -> ab -> a.apply(ab.a).apply(ab.b), ab -> a -> b -> ab.apply(new Tuple<>(a, b)));
	}

	/*
	 * 1 = S O (we are using peano arithmetic)
	 * https://en.wikipedia.org/wiki/Peano_axioms
	 */
	static ISO<Unit, Optional<Void>> one() {
		return iso(ignored -> Optional.empty(), ignored -> Unit.INSTANCE);
	}

	/* 2 = S (S O) */
	static ISO<Boolean, Optional<Optional<Void>>> two() {
		return iso(bool -> bool ? Optional.of(Optional.empty()) : Optional.empty(), Optional::isPresent);
	}


	/* 0 + b = b */
	static <B> ISO<Either<Void, B>, B> plusO() {
		return iso(vb -> vb.pm(Void::absurd, b -> b), Either::right);
	}

	/* S a + b = S (a + b) */
	static <A, B> ISO<Either<Optional<A>, B>, Optional<Either<A, B>>> plusS() {
		return iso(oab -> oab.pm(oa -> oa.map(a -> Optional.of(Either.<A, B>left(a))).orElseGet(
				() -> Optional.<Either<A, B>>empty()), b -> Optional.of(Either.right(b))),
				oab -> oab.<Either<Optional<A>, B>>map(
						ab -> ab.<Either<Optional<A>, B>>pm(a -> Either.<Optional<A>, B>left(Optional.of(a)),
								b -> Either.<Optional<A>, B>right(b))).orElseGet(() -> Either.left(Optional.<A>empty())));
	}

	/* 1 + b = S b */
	static <B> ISO<Either<Unit, B>, Optional<B>> plusSO() {
		return trans(isoPlus(one(), refl()), trans(plusS(), isoS(plusO())));
	}

	/* 0 * a = 0 */
	static <A> ISO<Tuple<Void, A>, Void> multO() {
		return iso(a -> a.a, Void::absurd);
	}

	/* S a * b = b + a * b */
	static <A, B> ISO<Tuple<Optional<A>, B>, Either<B, Tuple<A, B>>> multS() {
		return ISO.<Tuple<Optional<A>, B>, Either<B, Tuple<A, B>>>iso(
				oab -> oab.a.map(a -> Either.<B, Tuple<A, B>>right(new Tuple<>(a, oab.b))).orElseGet(() -> Either.left(oab.b)),
				bab -> bab.pm(b -> new Tuple<>(Optional.empty(), b), ab -> new Tuple<>(Optional.of(ab.a), ab.b)));
	}

	/* S a * b = b + a * b */
	static <B> ISO<Tuple<Unit, B>, B> multSO() {
		return trans(isoProd(one(), refl()), trans(multS(), trans(isoPlus(refl(), multO()), trans(plusComm(), plusO()))));
	}

	/* a ^ 0 = 1 */
	static <A> ISO<Function<Void, A>, Unit> powO() {
		return iso(ignored -> Unit.INSTANCE, unit -> Void::absurd);
	}

	/* a ^ (S b) = a * (a ^ b) */
	static <A, B> ISO<Function<Optional<B>, A>, Tuple<A, Function<B, A>>> powS() {
		return iso(func -> new Tuple<>(func.apply(Optional.empty()), func.compose(Optional::of)),
				tuple -> b -> b.map(tuple.b).orElseGet(() -> tuple.a));
	}

	/*
	 * a ^ 1 = a
	 * Go the hard way (like multSO, plusSO)
	 * to prove that you really get what is going on!
	 */
	@SuppressWarnings("unchecked")
	static <A> ISO<Function<Unit, A>, A> powSO() {
		return trans(isoPow(one(), refl()), trans(powS(), trans(isoProd(refl(), powO()), trans(multComm(), (ISO) multSO()))));
	}
}
