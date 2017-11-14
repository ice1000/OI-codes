using System;
using System.Collections.Generic;
using System.Linq;
using NUnit.Framework;
using static Isomorphism;

// ReSharper disable InconsistentNaming

[TestFixture]
public class IsomorphismTest
{
	private const string MEOW = "meow";
	private const string MOE = "moe";

	private static readonly ISO<bool, string> tISO =
		new ISO<bool, string>(it => it ? MEOW : MOE, MEOW.Equals);

	private static readonly ISO<Optional<bool>, Optional<bool>> mISO =
		new ISO<Optional<bool>, Optional<bool>>(it =>
			it.Map(b => b
				? (Optional<bool>) Optional<bool>.From(false)
				: Optional<bool>.Empty()).OrElseGet(() => Optional<bool>.From(true)), null);

	private static readonly ISO<bool, bool> bISO = IsoUnOptional(mISO);

	private static readonly ISO<Optional<bool>, Optional<bool>> badMISO =
		new ISO<Optional<bool>, Optional<bool>>(it => it.fmap(b => b
			? (Optional<bool>) Optional<bool>.From(false)
			: Optional<bool>.Empty()), null);

	private static readonly ISO<bool, bool> badISO = IsoUnOptional(badMISO);
	private static Func<A, A> lrl<A, B>(ISO<A, B> Iso) => it => Iso.Bw(Iso.Fw(it));
	private static Func<B, B> rlr<A, B>(ISO<A, B> Iso) => it => Iso.Fw(Iso.Bw(it));

	[Test]
	public void SubStLTest()
	{
		Assert.AreEqual(MEOW, SubStL(tISO)(true));
		Assert.AreEqual(false, SubStL(IsoBool())(false));
		Assert.AreEqual(true, SubStL(IsoBool())(true));
	}

	[Test]
	public void SubStRTest()
	{
		Assert.AreEqual(MEOW, SubStL(SubStR(new ISO<ISO<bool, string>, object>(null, e => tISO))(null))(true));
		Assert.AreEqual(true, SubStR(IsoBool())(true));
		Assert.AreEqual(false, SubStR(IsoBool())(false));
	}

	[Test]
	public void ReflTest()
	{
		Assert.AreEqual(MEOW, SubStL(SubStL(Refl<ISO<bool, string>>())(tISO))(true));
	}

	[Test]
	public void SymmTest()
	{
		Assert.AreEqual(MEOW, SubStR(Symm(tISO))(true));
	}

	[Test]
	public void TransTest()
	{
		Assert.AreEqual(MEOW, SubStL(Trans(Refl<bool>(), Trans(tISO, Refl<string>())))(true));
	}

	[Test]
	public void IsoTupleTest()
	{
		var tuple = SubStL(IsoTuple(tISO, tISO))(Tuple.Create(true, false));
		Assert.AreEqual(MEOW, tuple.Item1);
		Assert.AreEqual(MOE, tuple.Item2);
	}

	[Test]
	public void IsoListTest()
	{
		Assert.AreEqual(MEOW + MEOW + MOE,
			SubStL(IsoList(tISO))(new List<bool>(new[] {true, true, false}))
				.Aggregate((a, b) => a + b));
	}

	[Test]
	public void IsoFuncTest()
	{
		Assert.AreEqual(MEOW, SubStL(IsoFunc(Symm(tISO), tISO))(MEOW.Equals)(true));
	}

	[Test]
	public void IsoOptionalTest()
	{
		Assert.IsFalse(SubStL(IsoOptional(tISO))(Optional<bool>.Empty()).IsPresent());
		Assert.AreEqual(MEOW, SubStL(IsoOptional(tISO))(Optional<bool>.From(true)).Get());
	}

	[Test]
	public void IsoUnOptionalTest()
	{
		Assert.AreEqual(false, SubStL(bISO)(true));
		Assert.AreEqual(true, SubStL(bISO)(false));
		Assert.AreEqual(false, SubStL(badISO)(true));
		Assert.Throws(typeof(Exception), () => SubStL(badISO)(false));
	}

	[Test]
	public void IsoEitherTest()
	{
		Assert.AreEqual(Either<bool, string>.Left(false),
			SubStL(IsoEither(IsoBoolNot(), tISO))(Either<bool, bool>.Left(true)));
		Assert.AreEqual(Either<bool, string>.Left(true),
			SubStL(IsoEither(IsoBoolNot(), tISO))(Either<bool, bool>.Left(false)));
		Assert.AreEqual(Either<bool, string>.Right(MEOW),
			SubStL(IsoEither(IsoBoolNot(), tISO))(Either<bool, bool>.Right(true)));
	}

	private static List<Unit> lu() =>
		new List<Unit>
		{
			Unit.INSTANCE,
			Unit.INSTANCE,
			Unit.INSTANCE,
			Unit.INSTANCE,
			Unit.INSTANCE,
			Unit.INSTANCE,
			Unit.INSTANCE,
			Unit.INSTANCE
		};

	[Test]
	public void IsoEUTest()
	{
		Assert.AreEqual(lrl(IsoEU())(Either<List<Unit>, Unit>.Left(new List<Unit>())),
			Either<List<Unit>, Unit>.Left(new List<Unit>()));
		Assert.AreEqual(lrl(IsoEU())(Either<List<Unit>, Unit>.Left(lu())), Either<List<Unit>, Unit>.Left(lu()));
		Assert.AreEqual(lrl(IsoEU())(Either<List<Unit>, Unit>.Right(Unit.INSTANCE)),
			Either<List<Unit>, Unit>.Right(Unit.INSTANCE));
		Assert.AreEqual(rlr(IsoEU())(Either<List<Unit>, Void>.Left(new List<Unit>())),
			Either<List<Unit>, Unit>.Left(new List<Unit>()));
		Assert.AreEqual(rlr(IsoEU())(Either<List<Unit>, Void>.Left(lu())), Either<List<Unit>, Unit>.Left(lu()));
		Assert.AreEqual(SubStL(IsoEU())(Either<List<Unit>, Unit>.Right(Unit.INSTANCE))
			.Match(l => true, r => false), true);
	}

	[Test]
	public void IsoSymmTest()
	{
		Assert.AreEqual(MOE, SubStR(SubStR(IsoSymm<string, bool>())(tISO))(false));
	}

	[Test]
	public void CheatTest()
	{
		Assert.AreNotEqual(Either<bool, bool>.Left(true), Either<bool, bool>.Left(false));
		Assert.AreNotEqual(Either<bool, bool>.Left(true), Either<bool, bool>.Right(true));
		Assert.AreNotEqual(Either<int, int>.Left(233), Either<int, int>.Right(666));
		Assert.AreNotEqual(Either<int, int>.Left(233), Either<int, int>.Right(233));
		Assert.AreNotEqual(Either<int, int>.Left(233), Either<int, int>.Left(666));
		Assert.AreNotEqual(Optional<int>.From(666), Optional<int>.From(233));
		Assert.AreNotEqual(Optional<int>.From(666), Optional<int>.Empty());
	}
}
