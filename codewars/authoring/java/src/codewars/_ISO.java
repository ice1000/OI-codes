package codewars;

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
	/** go backward */
	abstract A bw(final B b);

	/** go forward */
	abstract B fw(final A a);
	/**
	 * Either in Haskell
	 *
	 * @param <L> left
	 * @param <R> right
	 */
	final static class Either<L, R> {
		final L l;
		final R r;

		Either(L l, R r) {
			this.l = l;
			this.r = r;
		}

		Either<R, L> invert() {
			return new Either<>(r, l);
		}

		static <L, R> Either<L, R> left(L l) {
			return new Either<>(l, null);
		}

		static <L, R> Either<L, R> right(R r) {
			return new Either<>(null, r);
		}

		<L2, R2> Either<L2, R2> map(Function<? super L, ? extends L2> lf, Function<? super R, ? extends R2> rf) {
			return new Either<>(null != l ? lf.apply(l) : null, null != r ? rf.apply(r) : null);
		}

		@Override
		@SuppressWarnings("unchecked")
		public boolean equals(Object o) {
			if (null == o || !(o instanceof Either<?, ?>)) return false;
			Either<L, R> either = (Either<L, R>) o;
			return l == either.l && r == either.r;
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
		@SuppressWarnings("unchecked")
		public boolean equals(Object o) {
			if (null == o || !(o instanceof Tuple<?, ?>)) return false;
			Tuple<A, B> tuple = (Tuple<A, B>) o;
			return a == tuple.a && b == tuple.b;
		}
	}

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

	/** given ISO a b, we can go from a to b */
	static <A, B> Function<A, B> subStL(final ISO<A, B> iso) {
		return iso::fw;
	}

	/** and vise versa */
	static <A, B> Function<B, A> subStR(final ISO<A, B> iso) {
		return iso::bw;
	}

	/** There can be more than one ISO a b */
	static ISO<Boolean, Boolean> isoBool() {
		return refl();
	}

	static ISO<Boolean, Boolean> isoBoolNot() {
		return iso(a -> !a, b -> !b);
	}

	/** isomorphism is reflexive */
	static <A> ISO<A, A> refl() {
		return iso(a -> a, b -> b);
	}

	/** isomorphism is symmetric */
	static <A, B> ISO<A, B> symm(final ISO<B, A> iso) {
		return iso(iso::bw, iso::fw);
	}

	/** isomorphism is transitive */
	static <A, B, C> ISO<A, C> trans(ISO<A, B> ab, ISO<B, C> bc) {
		return iso(a -> bc.fw(ab.fw(a)), c -> ab.bw(bc.bw(c)));
	}

	/** We can combine isomorphism */
	static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoTuple(ISO<A, B> ab, ISO<C, D> cd) {
		return iso(ac -> new Tuple<>(ab.fw(ac.a), cd.fw(ac.b)), bd -> new Tuple<>(ab.bw(bd.a), cd.bw(bd.b)));
	}

	/** This corresponds to `isoList` in Haskell */
	static <A, B> ISO<Stream<A>, Stream<B>> isoStream(ISO<A, B> iso) {
		return iso(as -> as.map(iso::fw), bs -> bs.map(iso::bw));
	}

	/** This corresponds to `isoMaybe` in Haskell */
	static <A, B> ISO<Optional<A>, Optional<B>> isoOptional(ISO<A, B> iso) {
		return iso(a -> a.map(iso::fw), b -> b.map(iso::bw));
	}

	static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoEither(ISO<A, B> ab, ISO<C, D> cd) {
		return iso(a -> a.map(ab::fw, cd::fw), b -> b.map(ab::bw, cd::bw));
	}

	/**
	 * Going another way is hard (and is generally impossible)
	 * Remember, for all valid ISO, converting and converting back
	 * is the same as the original value.
	 * You need this to prove some case are impossible.
	 */
	@SuppressWarnings("ConstantConditions")
	static <A, B> ISO<A, B> isoUnOptional(ISO<Optional<A>, Optional<B>> iso) {
		return iso(a -> iso.fw(Optional.of(a)).orElseGet(() -> iso.fw(Optional.empty()).get()),
				   b -> iso.bw(Optional.of(b)).orElseGet(() -> iso.bw(Optional.empty()).get()));
	}

	static <A, B, C, D> ISO<Function<A, C>, Function<B, D>> isoFunc(ISO<A, B> ab, ISO<C, D> cd) {
		return iso(ac -> a -> cd.fw(ac.apply(ab.bw(a))), bd -> b -> cd.bw(bd.apply(ab.fw(b))));
	}

	/** And we have isomorphism on isomorphism! */
	static <A, B> ISO<ISO<A, B>, ISO<B, A>> isoSymm() {
		return iso(ISO::symm, ISO::symm);
	}

	// ---------------------------

	static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoProd(ISO<A, B> ab, ISO<C, D> cd) {
		return isoTuple(ab, cd);
	}

	static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoPlus(ISO<A, B> ab, ISO<C, D> cd) {
		return isoEither(ab, cd);
	}

	static <A, B> ISO<Optional<A>, Optional<B>> isoS(ISO<A, B> iso) {
		return isoOptional(iso);
	}

	static <A, B, C, D> ISO<Function<A, C>, Function<B, D>> isoPow(ISO<A, B> ab, ISO<C, D> cd) {
		return isoFunc(ab, cd);
	}

	static <A, B> ISO<Either<A, B>, Either<B, A>> plusComm() {
		return iso(Either::invert, Either::invert);
	}

}
