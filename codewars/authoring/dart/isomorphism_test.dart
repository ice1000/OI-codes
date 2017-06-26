import 'package:test/test.dart';
import 'main.dart';

String cul(int i, bool b) => "$i $b";

String cur(Tuple<int, bool> a) => cul(a.a, a.b);

Function lrl<A, B>(ISO<A, B> iso) => (a) => iso.bw(iso.fw(a));

Function rlr<A, B>(ISO<A, B> iso) => (b) => iso.fw(iso.bw(b));

main() {
  String MEOW = "meow";
  String MOE = "moe";
  String str = "it was me, DIO!";
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
  });
}
