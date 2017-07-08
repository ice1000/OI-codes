package codewars;

import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;
import java.util.List;
import java.util.stream.Collectors;

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
										return ((Either<L, R>) rhs).<Boolean>pm(l::equals, rr -> false);
								}
        
								@Override
								public String toString() {
										return "left: " + l.toString();
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
										return ((Either<L, R>) rhs).<Boolean>pm(ll -> false, r::equals);
								}

								@Override
								public String toString() {
										return "right: " + r.toString();
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

		final static class Unit {
				public static Unit INSTANCE = new Unit();

				private Unit() {
				}
		}

		static abstract class Void {
				public abstract <T> T absurd();
		}

		private static <A, B> ISO<A, B> iso(Function<A, B> forward, Function<B, A> backward) {
				return new ISO<A, B>() {
						@Override public A bw(B b) { return backward.apply(b); }
						@Override public B fw(A a) { return forward.apply(a); }
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
		static <A, B, C, D> ISO<Tuple<A, C>, Tuple<B, D>> isoTuple
				(final ISO<A, B> ab, final ISO<C, D> cd) {
				return iso(ac -> new Tuple<>(ab.fw(ac.a), cd.fw(ac.b)),
									 bd -> new Tuple<>(ab.bw(bd.a), cd.bw(bd.b)));
		}

		static <A, B> ISO<Stream<A>, Stream<B>> isoStream(final ISO<A, B> iso) {
				return iso(as -> as.map(iso::fw), bs -> bs.map(iso::bw));
		}

		static <A, B> ISO<Optional<A>, Optional<B>> isoOptional(final ISO<A, B> iso) {
				return iso(a -> a.map(iso::fw), b -> b.map(iso::bw));
		}

		static <A, B, C, D> ISO<Either<A, C>, Either<B, D>> isoEither
				(final ISO<A, B> ab, final ISO<C, D> cd) {
				return iso(l -> l.pm(a -> Either.left(ab.fw(a)),
														 c -> Either.right(cd.fw(c))),
									 r -> r.pm(b -> Either.left(ab.bw(b)),
														 d -> Either.right(cd.bw(d))));
		}

		/*
		 * Going another way is hard (and is generally impossible)
		 * Remember, for all valid ISO, converting and converting back
		 * is the same as the original value.
		 * You need this to prove some case are impossible.
		 */
		static <A, B> ISO<A, B> isoUnOptional(final ISO<Optional<A>, Optional<B>> iso) {
				return iso(a -> iso.fw(Optional.of(a))
									 .orElseGet(() -> iso.fw(Optional.empty()).get()),
									 b -> iso.bw(Optional.of(b))
									 .orElseGet(() -> iso.bw(Optional.empty()).get()));
		}

		// We cannot have
		// isoUnEither ::
		// ISO (Either a b) (Either c d) -> ISO a c -> ISO b d.
		// Note that we have
		static ISO<Either<Stream<Unit>, Unit>, Either<Stream<Unit>, Void>>isoEU() {
				return iso(l -> l.pm(ll -> Either.left(Stream.concat(Stream.of(Unit.INSTANCE), ll)),
														 r -> Either.left(Stream.empty())),
									 r -> r.pm(l -> { 
													 List<Unit> lu = l.collect(Collectors.toList());
													 return lu.isEmpty() ? 
															 Either.right(Unit.INSTANCE) :
															 Either.left(Stream.generate
																					 (() -> Unit.INSTANCE).limit(lu.size() - 1));
											 },
											 Void::absurd));
    }

		// where (), the empty tuple, has 1 value, and Void has 0 value
		// If we have isoUnEither,
		// We have ISO () Void by calling isoUnEither isoEU
		// That is impossible, since we can get a Void by
		// substL on ISO () Void
		// So it is impossible to have isoUnEither

		static <A, B, C, D> ISO<Function<A, C>, Function<B, D>>
				isoFunc(final ISO<A, B> ab, final ISO<C, D> cd) {
				return iso(ac -> a -> cd.fw(ac.apply(ab.bw(a))),
									 bd -> b -> cd.bw(bd.apply(ab.fw(b))));
		}

		/* And we have isomorphism on isomorphism! */
		static <A, B> ISO<ISO<A, B>, ISO<B, A>> isoSymm() {
				return iso(ISO::symm, ISO::symm);
		}
}
