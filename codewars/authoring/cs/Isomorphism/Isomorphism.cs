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
	public static _Left<L, R> Left(L l)
	{
		return new _Left<L, R>(l);
	}

	public static _Right<L, R> Right(R r)
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

public abstract class Optional<T>
{
	public static Some<T> From(T obj)
	{
		return new Some<T>(obj);
	}

	public static None<T> Empty()
	{
		return new None<T>();
	}

	public abstract Optional<R> Map<R>(Func<T, R> f);
	public abstract Optional<R> fmap<R>(Func<T, Optional<R>> f);
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

		public override Optional<R> fmap<R>(Func<T, Optional<R>> f)
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
		public None()
		{
		}

		public override Optional<R> Map<R>(Func<T, R> f)
		{
			return new None<R>();
		}

		public override Optional<R> fmap<R>(Func<T, Optional<R>> f)
		{
			return new None<R>();
		}

		/// don't change this
		public override T Get()
		{
			throw new Exception("cannot get From null");
		}

		public override bool Equals(object obj)
		{
			return obj is None<T>;
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

//	public static ISO<Either<L, R>, Either<R, L>> IsoEither<L, R>() =>
//		new ISO<Either<L, R>, Either<R, L>>(
//			lr => lr.Match<Either<R, L>>(Either<R, L>.Right, Either<R, L>.Left),
//			rl => rl.Match<Either<L, R>>(Either<L, R>.Right, Either<L, R>.Left));

	public static ISO<Either<A, C>, Either<B, D>> IsoEither<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd)
	{
		return new ISO<Either<A, C>, Either<B, D>>(
			l => l.Match<Either<B, D>>(a => Either<B, D>.Left(ab.Fw(a)), c => Either<B, D>.Right(cd.Fw(c))),
			r => r.Match<Either<A, C>>(b => Either<A, C>.Left(ab.Bw(b)), d => Either<A, C>.Right(cd.Bw(d))));
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
			le => le.Match<Either<List<Unit>, Void>>(l =>
				{
					l.Insert(0, Unit.INSTANCE);
					return Either<List<Unit>, Void>.Left(l);
				},
				r => Either<List<Unit>, Void>.Left(new List<Unit>())),
			re => re.Match(l => l.Count != 0
				? (Either<List<Unit>, Unit>) Either<List<Unit>, Unit>.Left(l.Skip(1).ToList())
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
}