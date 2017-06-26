import 'package:test/test.dart';
import 'main.dart';

String MEOW = "meow";
String MOE = "moe";
String str = "it was me, DIO!";

String cul(int i, bool b) => "$i $b";
String cur(Tuple<int, bool> a) => cul(a.a, a.b);

Function lrl<A, B>(ISO<A, B> iso) => (a) => iso.bw(iso.fw(a));
Function rlr<A, B>(ISO<A, B> iso) => (b) => iso.fw(iso.bw(b));

ISO pa() => plusAssoc();
ISO ma() => multAssoc();
ISO di() => dist();
ISO cu() => curryISO();
ISO multSO_() => trans(isoProd(one(), refl()), trans(multS(), trans(isoPlus(refl(), multO()), trans(plusComm(), plusO()))));
ISO plusSO_() => trans(isoPlus(one(), refl()), trans(plusS(), isoS(plusO())));
ISO powSO_() => trans(isoPow(one(), refl()), trans(powS(), trans(isoProd(refl(), powO()), trans(multComm(), multSO()))));
ISO pss() => plusS();
ISO pso() => plusSO_();
ISO mss() => multS();
ISO mso() => multSO_();
ISO poss() => powS();
ISO poso() => powSO();
ISO poso_() => powSO_();

String func(int i) => new List.filled(i, "DA★ZE").reduce((a, b) => a + b);
String mfunc(Optional<int> i) => i.map(func).orElseGet(() => str);

main() {
  ISO<bool, String> tISO = new ISO((it) => it ? MEOW : MOE, (a) => a == MEOW);
  ISO<Optional<bool>, Optional<bool>> mISO = new ISO((it) =>
      it.map((b) => b ? Optional.from(false) : Optional.empty()).orElseGet(() => Optional.from(true)), null);
  ISO<bool, bool> bISO = isoUnOptional(mISO);
  ISO<Optional<bool>, Optional<bool>> badMISO = new ISO((it) =>
      it.fmap((b) => b ? Optional.from(false) : Optional.empty()), null);
  ISO<bool, bool> badISO = isoUnOptional(badMISO);
  List<int> lu = [1, 2, 3, 4, 5, 6, 7, 8];
  group("subSt", () {
    test("subStL", () {
      expect(subStL(tISO)(true), equals(MEOW));
      expect(subStL(isoBool())(false), equals(false));
      expect(subStL(isoBool())(true), equals(true));
    });
    test("subStR", () {
      expect(subStL(subStR(new ISO(null, (whatever) => tISO))(null))(true), equals(MEOW));
      expect(subStR(isoBool())(false), equals(false));
      expect(subStR(isoBool())(true), equals(true));
    });
  });
  group("law", () {
    test("refl", () => expect(subStL(subStL(refl())(tISO))(true), equals(MEOW)));
    test("symm", () => expect(subStR(symm(tISO))(true), equals(MEOW)));
    test("trans", () => expect(subStL(trans(refl(), trans(tISO, refl())))(true), equals(MEOW)));
  });
  group("isoCombine", () {
    test("isoTuple", () => expect(subStL(isoTuple(tISO, tISO))(new Tuple(true, false)), equals(new Tuple(MEOW, MOE))));
    test("isoList", () => expect(subStL(isoList(tISO))([true, true, false]), equals([MEOW, MEOW, MOE])));
    test("isoFunc", () => expect(subStL(isoFunc(symm(tISO), tISO))((obj) => MEOW == obj)(true), equals(MEOW)));
    test("isoOptional", () {
      expect(subStL(isoOptional(tISO))(Optional.empty()).isPresent(), isFalse);
      expect(subStL(isoOptional(tISO))(Optional.from(true)).get(), equals(MEOW));
    });
    test("isoUnOptional", () {
      expect(subStL(bISO)(true), isFalse);
      expect(subStL(bISO)(false), isTrue);
      expect(subStL(badISO)(true), isFalse);
      try {
        subStL(badISO)(false);
      } catch (e) {
        expect(e, "why");
      }
    });
    test("isoEither", () {
      expect(subStL(isoEither(isoBoolNot(), tISO))(Either.left(true)), equals(Either.left(false)));
      expect(subStL(isoEither(isoBoolNot(), tISO))(Either.left(false)), equals(Either.left(true)));
      expect(subStL(isoEither(isoBoolNot(), tISO))(Either.right(true)), equals(Either.right(MEOW)));
    });
    test("isoEU", () {
      expect(lrl(isoEU())(Either.left([])).get(), equals([]));
      expect(lrl(isoEU())(Either.left(lu)).get(), equals(lu));
      expect(lrl(isoEU())(Either.right(null)).get(), isNull);
      expect(rlr(isoEU())(Either.left([])).get(), equals([]));
      expect(rlr(isoEU())(Either.left(lu)).get(), equals(lu));
      expect(Either.isLeft(subStL(isoEU())(Either.right(null))), isTrue);
    });
    test("assoc", () {
      expect(lrl(pa())(Either.left(Either.left(233))), equals(Either.left(Either.left(233))));
      expect(lrl(pa())(Either.left(Either.right(true))), equals(Either.left(Either.right(true))));
      expect(lrl(pa())(Either.right(str)), equals(Either.right(str)));
      expect(rlr(pa())(Either.left(233)), equals(Either.left(233)));
      expect(rlr(pa())(Either.right(Either.left(true))), equals(Either.right(Either.left(true))));
      expect(rlr(pa())(Either.right(Either.right(str))), equals(Either.right(Either.right(str))));
    });
    test("dist", () {
      Tuple tuple = new Tuple(0, Either.left(true));
      expect(lrl(di())(tuple), equals(tuple));
      tuple = new Tuple(0, Either.right(str));
      expect(lrl(di())(tuple), equals(tuple));
      Either either = Either.left(new Tuple(0, true));
      expect(rlr(di())(either), equals(either));
      either = Either.right(new Tuple(0, str));
      expect(rlr(di())(either), equals(either));
    });
    test("curry", () {
      expect(lrl(cu())((a) => (b) => cul(a, b))(0)(true), equals(cul(0, true)));
      expect(rlr(cu())(cur)(new Tuple(0, true)), equals(cul(0, true)));
    });
    test("one", () {
      expect(lrl(one())(Unit.INSTANCE), equals(Unit.INSTANCE));
      expect(rlr(one())(Optional.empty()), equals(Optional.empty()));
    });
    test("two", () {
      expect(lrl(two())(true), isTrue);
      expect(lrl(two())(false), isFalse);
      expect(rlr(two())(Optional.empty()), equals(Optional.empty()));
      expect(rlr(two())(Optional.from(Optional.empty())), equals(Optional.from(Optional.empty())));
    });
    test("plus", () {
      expect(lrl(plusO())(Either.right(str)), equals(Either.right(str)));
      expect(rlr(plusO())(str), equals(str));
      expect(lrl(pss())(Either.left(Optional.from(str))), equals(Either.left(Optional.from(str))));
      expect(lrl(pss())(Either.left(Optional.empty())), equals(Either.left(Optional.empty())));
      expect(lrl(pss())(Either.right(233)), equals(Either.right(233)));
      expect(rlr(pss())(Optional.from(Either.left(str))), equals(Optional.from(Either.left(str))));
      expect(rlr(pss())(Optional.from(Either.right(233))), equals(Optional.from(Either.right(233))));
      expect(rlr(pss())(Optional.empty()), equals(Optional.empty()));
      expect(lrl(pso())(Either.left(Unit.INSTANCE)), equals(Either.left(Unit.INSTANCE)));
      expect(lrl(pso())(Either.right(233)), equals(Either.right(233)));
      expect(rlr(pso())(Optional.empty()), equals(Optional.empty()));
      expect(rlr(pso())(Optional.from(233)), equals(Optional.from(233)));
    });
    test("mult", () {
      expect(lrl(mss())(new Tuple(Optional.from(str), 233)), equals(new Tuple(Optional.from(str), 233)));
      expect(lrl(mss())(new Tuple(Optional.empty(), 233)), equals(new Tuple(Optional.empty(), 233)));
      expect(rlr(mss())(Either.left(233)), equals(Either.left(233)));
      expect(rlr(mss())(Either.right(new Tuple(str, 233))), equals(Either.right(new Tuple(str, 233))));
      expect(lrl(mso())(new Tuple(Unit.INSTANCE, true)), equals(new Tuple(Unit.INSTANCE, true)));
      expect(lrl(mso())(new Tuple(Unit.INSTANCE, false)), equals(new Tuple(Unit.INSTANCE, false)));
      expect(rlr(mso())(true), isTrue);
      expect(rlr(mso())(false), isFalse);
    });
    test("pow", () {
      expect(rlr(powO())(Unit.INSTANCE), equals(Unit.INSTANCE));
      expect(lrl(poss())(mfunc)(Optional.from(3)), equals("DA★ZEDA★ZEDA★ZE"));
      expect(lrl(poss())(mfunc)(Optional.empty()), equals(str));
      expect(rlr(poss())(new Tuple(str, func)).a, equals(str));
      expect(rlr(poss())(new Tuple(str, func)).b(3), equals("DA★ZEDA★ZEDA★ZE"));
      expect(lrl(poso())((unit) => str)(Unit.INSTANCE), equals(str));
      expect(rlr(poso())(str), equals(str));
      expect(lrl(poso_())((unit) => str)(Unit.INSTANCE), equals(str));
      expect(rlr(poso_())(str), equals(str));
    });
  });

  group("isoLaw", () => test("isoSymm", () => expect(subStR(subStR(isoSymm())(tISO))(false), MOE)));
  group("shouldntCheat", () {
    test("on Tuples", () =>
        expect(subStL(isoTuple(tISO, tISO))(new Tuple(true, false)) == new Tuple(MOE, MOE), isFalse));
    test("on Eithers", () {
      expect(subStL(isoEither(isoBoolNot(), tISO))(Either.left(true)) == Either.left(true), isFalse);
      expect(subStL(isoEither(isoBoolNot(), tISO))(Either.left(true)) == Either.right(false), isFalse);
      expect(subStL(isoEither(isoBoolNot(), tISO))(Either.left(true)) == Either.right(true), isFalse);
    });
    test("on Optionals", () {
      expect(rlr(two())(Optional.from(Optional.empty())) == equals(Optional.from(Optional.from(1))), isFalse);
      expect(rlr(two())(Optional.from(Optional.empty())) == equals(Optional.empty()), isFalse);
    });
  });
}


