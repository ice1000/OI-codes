using System;
using System.Collections.Generic;
using System.Linq;

// ReSharper disable InconsistentNaming
#pragma warning disable 693
#pragma warning disable 659

public abstract class Either<L, R>
{
	public abstract T Match<T>(Func<L, T> lt, Func<R, T> rt);
	public abstract override bool Equals(object obj);

	public static Either<L, R> Left(L l)
	{
		return new _Left<L, R>(l);
	}

	public static Either<L, R> Right(R r)
	{
		return new _Right<L, R>(r);
	}

	public class _Left<L, R> : Either<L, R>
	{
		private readonly L l;

		public _Left(L l)
		{
			this.l = l;
		}

		public override T Match<T>(Func<L, T> lt, Func<R, T> rt)
		{
			return lt(l);
		}

		public override bool Equals(object rhs)
		{
			return rhs is Either<L, R>
			       && ((Either<L, R>) rhs).Match(arg => l.Equals(arg), rr => false);
		}
	}

	public class _Right<L, R> : Either<L, R>
	{
		private readonly R r;

		public _Right(R r)
		{
			this.r = r;
		}

		public override T Match<T>(Func<L, T> lt, Func<R, T> rt)
		{
			return rt(r);
		}

		public override bool Equals(object rhs)
		{
			return rhs is Either<L, R>
			       && ((Either<L, R>) rhs).Match(ll => false, arg => r.Equals(arg));
		}
	}
}

public abstract class Void
{
	public abstract A Absurd<A>();
}

public class Unit
{
	private Unit()
	{
	}

	public static readonly Unit INSTANCE = new Unit();
}

/// <summary>
/// If there's a problem of variance,
/// the test will extract the value and compare.
/// </summary>
/// <typeparam name="T"></typeparam>
public abstract class Optional<T>
{
	public static Optional<T> From(T obj)
	{
		return new Some<T>(obj);
	}

	public static Optional<T> Empty()
	{
		return new None<T>();
	}

	public abstract Optional<R> Map<R>(Func<T, R> f);
	public abstract Optional<R> FlatMap<R>(Func<T, Optional<R>> f);
	public abstract T Get();
	public abstract T OrElseGet(Func<T> f);
	public abstract bool IsPresent();
	public abstract override bool Equals(object obj);

	public class Some<T> : Optional<T>
	{
		private readonly T _obj;

		public Some(T obj)
		{
			_obj = obj;
		}

		public override Optional<R> Map<R>(Func<T, R> f)
		{
			return new Some<R>(f(_obj));
		}

		public override Optional<R> FlatMap<R>(Func<T, Optional<R>> f)
		{
			return f(_obj);
		}

		public override bool Equals(object other)
		{
			return other is Some<T> && Equals(_obj, ((Some<T>) other)._obj);
		}

		public override T Get()
		{
			return _obj;
		}

		public override T OrElseGet(Func<T> f)
		{
			return _obj;
		}

		public override bool IsPresent()
		{
			return true;
		}
	}

	public class None<T> : Optional<T>
	{
		public override Optional<R> Map<R>(Func<T, R> f)
		{
			return new None<R>();
		}

		public override Optional<R> FlatMap<R>(Func<T, Optional<R>> f)
		{
			return new None<R>();
		}

		/// don't change this
		public override T Get()
		{
			throw new Exception("cannot get from null");
		}

		/// <summary>
		/// don't change this
		/// </summary>
		/// <param name="obj">other object</param>
		/// <returns>is equaled</returns>
		public override bool Equals(object obj)
		{
			return null != obj && obj.GetType().Name.Equals("None`1");
		}

		public override T OrElseGet(Func<T> f)
		{
			return f();
		}

		public override bool IsPresent()
		{
			return false;
		}
	}
}

public class ISO<A, B>
{
	public Func<A, B> Fw;
	public Func<B, A> Bw;

	public ISO(Func<A, B> fw, Func<B, A> bw)
	{
		Fw = fw;
		Bw = bw;
	}
}

/// so, when are two type, `a` and `b`, considered equal?
/// a definition might be, it is possible to go from `a` to `b`,
/// and from `b` to `a`.
/// Going a roundway trip should leave you the same value.
/// Unfortunately it is virtually impossible to test this in Haskell.
/// This is called Isomorphism.
///
/// ISO can also be simulated in C#.
///
/// Created by ice1000 on 17-6-19.
///
public static class Isomorphism
{
	/// given ISO a b, we can go from a to b
	public static Func<A, B> SubStL<A, B>(ISO<A, B> iso)
	{
		return iso.Fw;
	}

	/// and vise versa
	public static Func<B, A> SubStR<A, B>(ISO<A, B> iso)
	{
		return iso.Bw;
	}

	/// isomorphism is reflexive
	public static ISO<A, A> Refl<A>()
	{
		return new ISO<A, A>(a => a, a => a);
	}

	public static ISO<bool, bool> IsoBool()
	{
		return Refl<bool>();
	}

	public static ISO<bool, bool> IsoBoolNot()
	{
		return new ISO<bool, bool>(a => !a, b => !b);
	}

	/// isomorphism is symmetric
	public static ISO<A, B> Symm<A, B>(ISO<B, A> iso)
	{
		return new ISO<A, B>(iso.Bw, iso.Fw);
	}

	/// isomorphism is transitive
	public static ISO<A, C> Trans<A, B, C>(ISO<A, B> ab, ISO<B, C> bc)
	{
		return new ISO<A, C>(a => bc.Fw(ab.Fw(a)), c => ab.Bw(bc.Bw(c)));
	}

	/// we can combine isomorphism
	public static ISO<Tuple<A, C>, Tuple<B, D>> IsoTuple<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return new ISO<Tuple<A, C>, Tuple<B, D>>(
			ac => Tuple.Create(ab.Fw(ac.Item1), cd.Fw(ac.Item2)),
			bd => Tuple.Create(ab.Bw(bd.Item1), cd.Bw(bd.Item2)));
	}

	public static ISO<Either<A, C>, Either<B, D>> IsoEither<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return new ISO<Either<A, C>, Either<B, D>>(
			l => l.Match(a => Either<B, D>.Left(ab.Fw(a)), c => Either<B, D>.Right(cd.Fw(c))),
			r => r.Match(b => Either<A, C>.Left(ab.Bw(b)), d => Either<A, C>.Right(cd.Bw(d))));
	}

	public static ISO<List<A>, List<B>> IsoList<A, B>(ISO<A, B> iso)
	{
		return new ISO<List<A>, List<B>>(a => a.ConvertAll(i => iso.Fw(i)), b => b.ConvertAll(i => iso.Bw(i)));
	}

	public static ISO<Optional<A>, Optional<B>> IsoOptional<A, B>(ISO<A, B> iso)
	{
		return new ISO<Optional<A>, Optional<B>>(a => a.Map(iso.Fw), b => b.Map(iso.Bw));
	}

	// We cannot have
	// isoUnEither ::
	// ISO (Either a b) (Either c d) -> ISO a c -> ISO b d.
	// Note that we have
	public static ISO<Either<List<Unit>, Unit>, Either<List<Unit>, Void>> IsoEU()
	{
		return new ISO<Either<List<Unit>, Unit>, Either<List<Unit>, Void>>(
			le => le.Match(l =>
				{
					l.Insert(0, Unit.INSTANCE);
					return Either<List<Unit>, Void>.Left(l);
				},
				r => Either<List<Unit>, Void>.Left(new List<Unit>())),
			re => re.Match(l => l.Count != 0
				? Either<List<Unit>, Unit>.Left(l.Skip(1).ToList())
				: Either<List<Unit>, Unit>.Right(Unit.INSTANCE), r => r.Absurd<Either<List<Unit>, Unit>>()));
	}
	// where (), the empty tuple, has 1 value, and Void has 0 value
	// If we have isoUnEither,
	// We have ISO () Void by calling isoUnEither isoEU
	// That is impossible, since we can get a Void by
	// substL on ISO () Void
	// So it is impossible to have isoUnEither


	/// Going another way is hard (and is generally impossible)
	/// Remember, for all valid ISO, converting and converting back
	/// is the same as the original value.
	/// You need this to prove some case are impossible.
	public static ISO<A, B> IsoUnOptional<A, B>(ISO<Optional<A>, Optional<B>> iso)
	{
		return new ISO<A, B>(
			a => iso.Fw(Optional<A>.From(a)).OrElseGet(() => iso.Fw(Optional<A>.Empty()).Get()),
			b => iso.Bw(Optional<B>.From(b)).OrElseGet(() => iso.Bw(Optional<B>.Empty()).Get()));
	}

	public static ISO<Func<A, C>, Func<B, D>> IsoFunc<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return new ISO<Func<A, C>, Func<B, D>>(ac => a => cd.Fw(ac(ab.Bw(a))), bd => b => cd.Bw(bd(ab.Fw(b))));
	}

	/// And we have isomorphism on isomorphism!
	public static ISO<ISO<A, B>, ISO<B, A>> IsoSymm<A, B>()
	{
		return new ISO<ISO<A, B>, ISO<B, A>>(Symm, Symm);
	}

	///  *** MENTION ***  ///
	///  paste your code  ///
	/// from isomorphism  ///
	///  *** MENTION ***  ///

	// C# specific notes:
	// Optional.fmap is renamed to Optional.FlatMap

	// Sometimes, we can treat a Type as a Number:
	/// if a Type t has n distinct value, it's Number is n.
	/// This is formally called cardinality.
	/// See https://en.wikipedia.org/wiki/Cardinality
	///
	/// Void has cardinality of 0 (we will abbreviate it Void is 0).
	/// () is 1.
	/// Bool is 2.
	/// Maybe a is 1 + a.
	/// We will be using peano arithmetic so we will write it as S a.
	/// https://en.wikipedia.org/wiki/Peano_axioms
	/// Either a b is a + b.
	/// (a, b) is a * b.
	/// a => b is b ^ a. Try counting (() => Bool) and (Bool => ())
	///
	/// Algebraic data type got the name because
	/// it satisfies a lot of algebraic rules under isomorphism
	/// a = b => c = d => a * c = b * d
	public static ISO<Tuple<A, C>, Tuple<B, D>> isoProd<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return IsoTuple(ab, cd);
	}

	/// a = b => c = d => a + c = b + d
	public static ISO<Either<A, C>, Either<B, D>> IsoPlus<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return IsoEither(ab, cd);
	}

	/// a = b => S a = S b
	public static ISO<Optional<A>, Optional<B>> IsoS<A, B>(ISO<A, B> iso)
	{
		return IsoOptional(iso);
	}

	/// a = b => c = d => c ^ a = d ^ b
	public static ISO<Func<A, C>, Func<B, D>> IsoPow<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return IsoFunc(ab, cd);
	}

	/// a + b = b + a
	public static ISO<Either<L, R>, Either<R, L>> PlusComm<L, R>()
	{
		return new ISO<Either<L, R>, Either<R, L>>(
			lr => lr.Match(Either<R, L>.Right, Either<R, L>.Left),
			rl => rl.Match(Either<L, R>.Right, Either<L, R>.Left));
	}

	/// a + b + c = a + (b + c)
	public static ISO<Either<Either<A, B>, C>, Either<A, Either<B, C>>> PlusAssoc<A, B, C>()
	{
		return new ISO<Either<Either<A, B>, C>, Either<A, Either<B, C>>>(
			abc => abc.Match(ab => ab.Match(
					Either<A, Either<B, C>>.Left,
					b => Either<A, Either<B, C>>.Right(Either<B, C>.Left(b))),
				c => Either<A, Either<B, C>>.Right(Either<B, C>.Right(c))),
			abc => abc.Match(
				a => Either<Either<A, B>, C>.Left(Either<A, B>.Left(a)),
				bc => bc.Match(b => Either<Either<A, B>, C>.Left(Either<A, B>.Right(b)),
					Either<Either<A, B>, C>.Right)));
	}

	/// a * b = b * a
	public static ISO<Tuple<A, B>, Tuple<B, A>> MultComm<A, B>()
	{
		return new ISO<Tuple<A, B>, Tuple<B, A>>(ab => Tuple.Create(ab.Item2, ab.Item1),
			ba => Tuple.Create(ba.Item2, ba.Item1));
	}

	/// a * b * c = a * (b * c)
	public static ISO<Tuple<Tuple<A, B>, C>, Tuple<A, Tuple<B, C>>> PultAssoc<A, B, C>()
	{
		return new ISO<Tuple<Tuple<A, B>, C>, Tuple<A, Tuple<B, C>>>(
			a => Tuple.Create(a.Item1.Item1, Tuple.Create(a.Item1.Item2, a.Item2)),
			a => Tuple.Create(Tuple.Create(a.Item1, a.Item2.Item1), a.Item2.Item2));
	}


	/// a * (b + c) = a * b + a * c
	public static ISO<Tuple<A, Either<B, C>>, Either<Tuple<A, B>, Tuple<A, C>>> Dist<A, B, C>()
	{
		return new ISO<Tuple<A, Either<B, C>>, Either<Tuple<A, B>, Tuple<A, C>>>(
			abc => abc.Item2.Match(
				b => Either<Tuple<A, B>, Tuple<A, C>>.Left(Tuple.Create(abc.Item1, b)),
				c => Either<Tuple<A, B>, Tuple<A, C>>.Right(Tuple.Create(abc.Item1, c))),
			abac => abac.Match(
				ab => Tuple.Create(ab.Item1, Either<B, C>.Left(ab.Item2)),
				ac => Tuple.Create(ac.Item1, Either<B, C>.Right(ac.Item2))));
	}

	/// (c ^ b) ^ a = c ^ (a * b)
	public static ISO<Func<A, Func<B, C>>, Func<Tuple<A, B>, C>> CurryISO<A, B, C>()
	{
		return new ISO<Func<A, Func<B, C>>, Func<Tuple<A, B>, C>>(
			a => ab => a(ab.Item1)(ab.Item2),
			ab => a => b => ab(Tuple.Create(a, b)));
	}


	/// 1 = S O (we are using peano arithmetic)
	/// https://en.wikipedia.org/wiki/Peano_axioms
	public static ISO<Unit, Optional<Void>> One()
	{
		return new ISO<Unit, Optional<Void>>(_ => Optional<Void>.Empty(), _ => Unit.INSTANCE);
	}

	/// 2 = S (S O)
	public static ISO<bool, Optional<Optional<Void>>> Two()
	{
		return new ISO<bool, Optional<Optional<Void>>>(
			b => b ? Optional<Optional<Void>>.From(Optional<Void>.Empty()) : Optional<Optional<Void>>.Empty(),
			option => option.IsPresent());
	}

	/// 0 + b = b
	public static ISO<Either<Void, B>, B> PlusO<B>()
	{
		return new ISO<Either<Void, B>, B>(vb => vb.Match(v => v.Absurd<B>(), b => b), Either<Void, B>.Right);
	}

	/// S a + b = S (a + b)
	public static ISO<Either<Optional<A>, B>, Optional<Either<A, B>>> PlusS<A, B>()
	{
		return new ISO<Either<Optional<A>, B>, Optional<Either<A, B>>>(
			oab => oab.Match(oa => oa.Map(a => Optional<Either<A, B>>.From(Either<A, B>.Left(a)))
					.OrElseGet(Optional<Either<A, B>>.Empty),
				b => Optional<Either<A, B>>.From(Either<A, B>.Right(b))),
			oab => oab.Map(ab =>
					ab.Match(a => Either<Optional<A>, B>.Left(Optional<A>.From(a)), Either<Optional<A>, B>.Right))
				.OrElseGet(() => Either<Optional<A>, B>.Left(Optional<A>.Empty())));
	}

	/// 1 + b = S b
	public static ISO<Either<Unit, B>, Optional<B>> PlusSO<B>()
	{
		return Trans(IsoPlus(One(), Refl<B>()), Trans(PlusS<Void, B>(), IsoS(PlusO<B>())));
	}

	/// 0 * a = 0
	public static ISO<Tuple<Void, A>, Void> MultO<A>()
	{
		return new ISO<Tuple<Void, A>, Void>(a => a.Item1, v => v.Absurd<Tuple<Void, A>>());
	}

	/// S a * b = b + a * b
	public static ISO<Tuple<Optional<A>, B>, Either<B, Tuple<A, B>>> MultS<A, B>()
	{
		return new ISO<Tuple<Optional<A>, B>, Either<B, Tuple<A, B>>>(
			oab => oab.Item1.Map(a => Either<B, Tuple<A, B>>.Right(Tuple.Create(a, oab.Item2)))
				.OrElseGet(() => Either<B, Tuple<A, B>>.Left(oab.Item2)),
			bab => bab.Match(b => Tuple.Create(Optional<A>.Empty(), b),
				ab => Tuple.Create(Optional<A>.From(ab.Item1), ab.Item2)));
	}

	/// S 1 * b = b + 1 * b
	public static ISO<Tuple<Unit, B>, B> MultSO<B>()
	{
		return Trans(isoProd(One(), Refl<B>()), Trans(MultS<Void, B>(),
			Trans(IsoPlus(Refl<B>(), MultO<B>()), Trans(PlusComm<B, Void>(), PlusO<B>()))));
	}

	/// a ^ 0 = 1
	public static ISO<Func<Void, A>, Unit> PowO<A>()
	{
		return new ISO<Func<Void, A>, Unit>(_ => Unit.INSTANCE, _ => v => v.Absurd<A>());
	}

	/// a ^ (S b) = a * (a ^ b)
	public static ISO<Func<Optional<B>, A>, Tuple<A, Func<B, A>>> PowS<A, B>()
	{
		return new ISO<Func<Optional<B>, A>, Tuple<A, Func<B, A>>>(
			func => Tuple.Create<A, Func<B, A>>(func(Optional<B>.Empty()), o => func(Optional<B>.From(o))),
			tuple => b => b.Map(tuple.Item2).OrElseGet(() => tuple.Item1));
	}

	/// a ^ 1 = a
	/// Go the hard way (like MultSO, PlusSO)
	/// to prove that you really get what is going on!
	public static ISO<Func<Unit, A>, A> PowSO<A>()
	{
		return Trans(IsoPow(One(), Refl<A>()), Trans(PowS<A, Void>(),
			Trans(isoProd(Refl<A>(), PowO<A>()), Trans(MultComm<A, Unit>(), MultSO<A>()))));
	}
}