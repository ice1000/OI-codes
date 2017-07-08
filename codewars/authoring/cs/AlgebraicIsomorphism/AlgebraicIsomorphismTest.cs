using System;
using System.Collections.Generic;
using System.Linq;
using NUnit.Framework;
using static Isomorphism;

//using StupidVoid = System.Void;

// ReSharper disable InconsistentNaming

[TestFixture]
public class IsomorphismTest
{
	private const string MEOW = "meow";
	private const string MOE = "moe";
	private const string str = "It was me, DIO!";

	private static readonly ISO<bool, string> tISO =
		new ISO<bool, string>(it => it ? MEOW : MOE, MEOW.Equals);

	private static readonly ISO<Optional<bool>, Optional<bool>> mISO =
		new ISO<Optional<bool>, Optional<bool>>(it =>
			it.Map(b => b
				? Optional<bool>.From(false)
				: Optional<bool>.Empty()).OrElseGet(() => Optional<bool>.From(true)), null);

	private static readonly ISO<bool, bool> bISO = IsoUnOptional(mISO);

	private static readonly ISO<Optional<bool>, Optional<bool>> badMISO =
		new ISO<Optional<bool>, Optional<bool>>(it => it.FlatMap(b => b
			? Optional<bool>.From(false)
			: Optional<bool>.Empty()), null);

	private static readonly ISO<bool, bool> badISO = IsoUnOptional(badMISO);

	private static Func<A, A> Lrl<A, B>(ISO<A, B> Iso)
	{
		return it => Iso.Bw(Iso.Fw(it));
	}

	private static Func<B, B> Rlr<A, B>(ISO<A, B> Iso)
	{
		return it => Iso.Fw(Iso.Bw(it));
	}

	private static string Cul(int i, bool b)
	{
		return i + " " + b;
	}

	private static string Cur(Tuple<int, bool> tuple)
	{
		return Cul(tuple.Item1, tuple.Item2);
	}

	private static ISO<Func<Unit, A>, A> PowSO_<A>()
	{
		return Trans(IsoPow(One(), Refl<A>()),
			Trans(PowS<A, Void>(), Trans(isoProd(Refl<A>(), PowO<A>()), Trans(MultComm<A, Unit>(), MultSO_<A>()))));
	}

	public static ISO<Tuple<Unit, B>, B> MultSO_<B>()
	{
		return Trans(isoProd(One(), Refl<B>()),
			Trans(MultS<Void, B>(), Trans(IsoPlus(Refl<B>(), MultO<B>()), Trans(PlusComm<B, Void>(), PlusO<B>()))));
	}

	public static ISO<Either<Unit, B>, Optional<B>> PlusSO_<B>()
	{
		return Trans(IsoPlus(One(), Refl<B>()), Trans(PlusS<Void, B>(), IsoS(PlusO<B>())));
	}

	/* master spark! */
	private static string FuncIntStr(int integer)
	{
		var strings = new string[integer];
		for (var i = 0; i < strings.Length; i++)
			strings[i] = "DA★ZE";
		return string.Join("|", strings);
	}

	private static string MaybeFunc(Optional<int> optional)
	{
		return optional.Map(FuncIntStr).OrElseGet(() => str);
	}

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

	[Test]
	public void IsoSymmTest()
	{
		Assert.AreEqual(MOE, SubStR(SubStR(IsoSymm<string, bool>())(tISO))(false));
	}

	[Test]
	public void CheatTest()
	{
		Console.WriteLine(
			"Don't change the <p><font color=\"BLUE\">Equals</font></p>" +
			" method of <p><font color=\"YELLOW\">Either</font></p> and " +
			"<p><font color=\"YELLOW\">Optional</font></p>!");
		var val = new Random(DateTime.Now.Millisecond).Next();
		Assert.AreNotEqual(Either<bool, bool>.Left(true), Either<bool, bool>.Left(false));
		Assert.AreNotEqual(Either<bool, bool>.Left(true), Either<bool, bool>.Right(true));
		Assert.AreNotEqual(Either<int, int>.Left(val), Either<int, int>.Right(val + 1));
		Assert.AreNotEqual(Either<int, int>.Left(val), Either<int, int>.Right(val));
		Assert.AreNotEqual(Either<int, int>.Left(val), Either<int, int>.Left(val + 1));
		Assert.AreNotEqual(Optional<int>.From(val + 1), Optional<int>.From(val));
		Assert.AreNotEqual(Optional<int>.From(666), Optional<int>.Empty());
		Assert.AreEqual(Optional<int>.Empty(), Optional<int>.Empty());
	}


	[Test]
	public void Assoc()
	{
		var val = new Random(DateTime.Now.Millisecond).Next();
		Assert.AreEqual(Either<Either<int, bool>, bool>.Left(Either<int, bool>.Left(val)),
			Lrl(PlusAssoc<int, bool, bool>())(Either<Either<int, bool>, bool>.Left(Either<int, bool>.Left(val))));
		Assert.AreEqual(Either<Either<int, bool>, bool>.Left(Either<int, bool>.Right(true)),
			Lrl(PlusAssoc<int, bool, bool>())(Either<Either<int, bool>, bool>.Left(Either<int, bool>.Right(true))));
		Assert.AreEqual(Either<Either<int, bool>, string>.Right(str),
			Lrl(PlusAssoc<int, bool, string>())(Either<Either<int, bool>, string>.Right(str)));
		Assert.AreEqual(Either<int, Either<bool, string>>.Left(val),
			Rlr(PlusAssoc<int, bool, string>())(Either<int, Either<bool, string>>.Left(val)));
		Assert.AreEqual(Either<bool, Either<bool, string>>.Right(Either<bool, string>.Left(true)),
			Rlr(PlusAssoc<bool, bool, string>())(Either<bool, Either<bool, string>>.Right(Either<bool, string>.Left(true))));
		Assert.AreEqual(Either<bool, Either<bool, string>>.Right(Either<bool, string>.Right(str)),
			Rlr(PlusAssoc<bool, bool, string>())(Either<bool, Either<bool, string>>.Right(Either<bool, string>.Right(str))));
	}

	[Test]
	public void DistTest()
	{
		var tuple = new Tuple<int, Either<bool, string>>(0, Either<bool, string>.Left(true));
		Assert.AreEqual(tuple, Lrl(Dist<int, bool, string>())(tuple));
		var tuple2 = new Tuple<int, Either<bool, string>>(0, Either<bool, string>.Right(str));
		Assert.AreEqual(tuple2, Lrl(Dist<int, bool, string>())(tuple2));
		var either = Either<Tuple<int, bool>, Tuple<int, string>>.Left(new Tuple<int, bool>(0, true));
		Assert.AreEqual(either, Rlr(Dist<int, bool, string>())(either));
		var either2 = Either<Tuple<int, bool>, Tuple<int, string>>.Right(new Tuple<int, string>(0, str));
		Assert.AreEqual(either2, Rlr(Dist<int, bool, string>())(either2));
	}

	[Test]
	public void CurryTest()
	{
		Assert.AreEqual(Cul(0, true), Lrl(CurryISO<int, bool, string>())(a => b => Cul(a, b))(0)(true));
		Assert.AreEqual(Cul(0, true), Rlr(CurryISO<int, bool, string>())(Cur)(new Tuple<int, bool>(0, true)));
	}

	[Test]
	public void OneTest()
	{
		Assert.AreEqual(Unit.INSTANCE, Lrl(One())(Unit.INSTANCE));
		Assert.AreEqual(Optional<Void>.Empty(), Rlr(One())(Optional<Void>.Empty()));
	}

	[Test]
	public void TwoTest()
	{
		Assert.IsTrue(Lrl(Two())(true));
		Assert.IsFalse(Lrl(Two())(false));
		Assert.AreEqual(Optional<Optional<Void>>.Empty(), Rlr(Two())(Optional<Optional<Void>>.Empty()));
		Assert.AreEqual(Optional<Optional<Void>>.From(Optional<Void>.Empty()),
			Rlr(Two())(Optional<Optional<Void>>.From(Optional<Void>.Empty())));
	}

	[Test]
	public void PlusTest()
	{
		var val = new Random(DateTime.Now.Millisecond).Next();
		Assert.AreEqual(Either<Void, string>.Right(str), Lrl(PlusO<string>())(Either<Void, string>.Right(str)));
		Assert.AreEqual(str, Rlr(PlusO<string>())(str));
		Assert.AreEqual(Either<Optional<string>, int>.Left(Optional<string>.From(str)),
			Lrl(PlusS<string, int>())(Either<Optional<string>, int>.Left(Optional<string>.From(str))));
		Assert.AreEqual(Either<Optional<string>, int>.Left(Optional<string>.Empty()),
			Lrl(PlusS<string, int>())(Either<Optional<string>, int>.Left(Optional<string>.Empty())));
		Assert.AreEqual(Either<Optional<string>, int>.Right(val),
			Lrl(PlusS<string, int>())(Either<Optional<string>, int>.Right(val)));
		Assert.AreEqual(Optional<Either<string, int>>.From(Either<string, int>.Left(str)),
			Rlr(PlusS<string, int>())(Optional<Either<string, int>>.From(Either<string, int>.Left(str))));
		Assert.AreEqual(Optional<Either<string, int>>.From(Either<string, int>.Right(val)),
			Rlr(PlusS<string, int>())(Optional<Either<string, int>>.From(Either<string, int>.Right(val))));
		Assert.AreEqual(Optional<Either<string, int>>.Empty(),
			Rlr(PlusS<string, int>())(Optional<Either<string, int>>.Empty()));
		Assert.AreEqual(Either<Unit, int>.Left(Unit.INSTANCE), Lrl(PlusSO_<int>())(Either<Unit, int>.Left(Unit.INSTANCE)));
		Assert.AreEqual(Either<Unit, int>.Right(val), Lrl(PlusSO_<int>())(Either<Unit, int>.Right(val)));
		Assert.AreEqual(Optional<int>.Empty(), Rlr(PlusSO_<int>())(Optional<int>.Empty()));
		Assert.AreEqual(val, Rlr(PlusSO_<int>())(Optional<int>.From(val)).Get());
		Assert.AreEqual(Either<Unit, int>.Left(Unit.INSTANCE), Lrl(PlusSO<int>())(Either<Unit, int>.Left(Unit.INSTANCE)));
		Assert.AreEqual(Either<Unit, int>.Right(val), Lrl(PlusSO<int>())(Either<Unit, int>.Right(val)));
		Assert.AreEqual(Optional<int>.Empty(), Rlr(PlusSO<int>())(Optional<int>.Empty()));
		Assert.AreEqual(val, Rlr(PlusSO<int>())(Optional<int>.From(val)).Get());
	}

	[Test]
	public void multTest()
	{
		var val = new Random(DateTime.Now.Millisecond).Next();
		Assert.AreEqual(Tuple.Create(Optional<string>.From(str), val),
			Lrl(MultS<string, int>())(Tuple.Create(Optional<string>.From(str), val)));
		Assert.AreEqual(Tuple.Create(Optional<string>.Empty(), val),
			Lrl(MultS<string, int>())(Tuple.Create(Optional<string>.Empty(), val)));
		Assert.AreEqual(Either<int, Tuple<string, int>>.Left(val),
			Rlr(MultS<string, int>())(Either<int, Tuple<string, int>>.Left(val)));
		Assert.AreEqual(Either<int, Tuple<string, int>>.Right(Tuple.Create(str, val)),
			Rlr(MultS<string, int>())(Either<int, Tuple<string, int>>.Right(Tuple.Create(str, val))));
		Assert.AreEqual(Tuple.Create(Unit.INSTANCE, true), Lrl(MultSO<bool>())(Tuple.Create(Unit.INSTANCE, true)));
		Assert.AreEqual(Tuple.Create(Unit.INSTANCE, false), Lrl(MultSO<bool>())(Tuple.Create(Unit.INSTANCE, false)));
		Assert.IsTrue(Rlr(MultSO<bool>())(true));
		Assert.IsFalse(Rlr(MultSO<bool>())(false));
	}

	[Test]
	public void powTest()
	{
		Assert.AreEqual(Unit.INSTANCE, Rlr(PowO<Unit>())(Unit.INSTANCE));
		Assert.AreEqual("DA★ZE|DA★ZE|DA★ZE", Lrl(PowS<string, int>())(MaybeFunc)(Optional<int>.From(3)));
		Assert.AreEqual(str, Lrl(PowS<string, int>())(MaybeFunc)(Optional<int>.Empty()));
		Assert.AreEqual(str, Rlr(PowS<string, int>())(Tuple.Create<string, Func<int, string>>(str, FuncIntStr)).Item1);
		Assert.AreEqual("DA★ZE|DA★ZE|DA★ZE",
			Rlr(PowS<string, int>())(Tuple.Create<string, Func<int, string>>(str, FuncIntStr)).Item2(3));
		Assert.AreEqual(str, Lrl(PowSO<string>())(unit => str)(Unit.INSTANCE));
		Assert.AreEqual(str, Rlr(PowSO<string>())(str));
		Assert.AreEqual(str, Lrl(PowSO_<string>())(unit => str)(Unit.INSTANCE));
		Assert.AreEqual(str, Rlr(PowSO_<string>())(str));
	}
}