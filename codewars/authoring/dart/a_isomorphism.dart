/// so, when are two type, `a` and `b`, considered equal?
/// a definition might be, it is possible to go from `a` to `b`,
/// and from `b` to `a`.
/// Going a roundway trip should leave you the same value.
/// Unfortunately it is virtually impossible to test this in Haskell.
/// This is called ISO.
///
/// ISO can be simulated in Dart.
/// Dart doesn't support Functions like Function<A, B> so I'll
/// put the expected param/return type in the doc comment.
///
class ISO<A, B> {
  Function _bw, _fw;
  ISO(this._fw, this._bw);
  /// go backward
  A bw(final B b) => _bw(b);
  /// go forward
  B fw(final A a) => _fw(a);
}

abstract class Either<L, R> {
  T pm<T>(Function lt, Function rt);
  static _Left<L, R> left<L, R>(L l) => new _Left(l);
  static _Right<L, R> right<L, R>(R r) => new _Right(r);
  static isLeft(Either e) => e is _Left;
  static isRight(Either e) => e is _Right;
  L getLeft();
  R getRight();
}

class _Left<L, R> extends Either<L, R> {
  L _l;
  _Left(this._l);
  @override dynamic get() => _l;
  @override T pm<T>(Function lt, Function rt) => lt(_l);
  @override bool operator ==(Object rhs) => (rhs as Either<L, R>).pm((o) => _l == o, (rr) => false);
  @override L getLeft() => _l;
  @override R getRight() => throw _l;
}

class _Right<L, R> extends Either<L, R> {
  L _r;
  _Right(this._r);
  @override dynamic get() => _r;
  @override T pm<T>(Function lt, Function rt) => rt(_r);
  @override bool operator ==(Object rhs) => (rhs as Either<L, R>).pm((ll) => false, (o) => _r == o);
  @override L getLeft() => throw _r;
  @override R getRight() => _r;
}

class Tuple<A, B> {
  A a;
  B b;
  Tuple(this.a, this.b);
  @override bool operator ==(other) => other is Tuple<A, B> && other.a == a && other.b == b;
}

abstract class Optional<T> {
  static _None _none = new _None();
  static _Some<T> from<T> (T obj) => new _Some(obj);
  static _None empty() => _none;
  static bool hasValue<T>(Optional<T> o) => o.isPresent();
  @override bool operator ==(other);
  Optional<E> map<E>(Function f);
  Optional<E> fmap<E>(Function f);
  T get();
  T orElseGet(Function f);
  bool isPresent();
}

class _Some<T> extends Optional<T> {
  T _obj;
  _Some(this._obj);
  @override _Some<E> map<E>(Function f) => new _Some(f(_obj));
  @override Optional<E> fmap<E>(Function f) => f(_obj);
  @override bool operator ==(other) => other is _Some && _obj == other._obj;
  @override T get() => _obj;
  @override T orElseGet(Function f) => _obj;
  @override bool isPresent() => true;
}

class _None<T> extends Optional<T> {
  _None();
  @override _None map(Function f) => this;
  @override _None fmap(Function f) => this;
  @override bool operator ==(other) => true;
  /// don't change this
  @override T get() => throw "why";
  @override T orElseGet(Function f) => f();
  @override bool isPresent() => false;
}

abstract class Void {
  static A absurd<A>(Void v) { throw v; }
}

class Unit {
  Unit();
  static Unit INSTANCE = new Unit();
}

/// given ISO a b, we can go from a to b
Function subStL<A, B>(ISO<A, B> iso) => iso.fw;

/// and vise versa
Function subStR<A, B>(ISO<A, B> iso) => iso.bw;

/// There can be more than one ISO a b
ISO<bool, bool> isoBool() => refl();

ISO<bool, bool> isoBoolNot() => new ISO((a) => !a, (b) => !b);

/// isomorphism is reflexive
ISO<A, A> refl<A>() => new ISO((a) => a, (b) => b);

/// isomorphism is symmetric
ISO<A, B> symm<A, B>(final ISO<B, A> iso) => new ISO(iso.bw, iso.fw);

/// isomorphism is transitive
ISO<A, C> trans<A, B, C>(final ISO<A, B> ab, final ISO<B, C> bc) => new ISO((a) => bc.fw(ab.fw(a)), (c) => ab.bw(bc.bw(c)));

/// we can combine isomorphism
ISO<Tuple<A, C>, Tuple<B, D>> isoTuple<A, B, C, D>(final ISO<A, B> ab, final ISO<C, D> cd) => new ISO((ac) => new Tuple(ab.fw(ac.a), cd.fw(ac.b)), (bd) => new Tuple(ab.bw(bd.a), cd.bw(bd.b)));

ISO<List<A>, List<B>> isoList<A, B>(final ISO<A, B> iso) => new ISO((as) => as.map(iso.fw), (bs) => bs.map(iso.bw));

ISO<Optional<A>, Optional<B>> isoOptional<A, B>(final ISO<A, B> iso) => new ISO((a) => a.map(iso.fw), (b) => b.map(iso.bw));

ISO<Either<A, C>, Either<B, D>> isoEither<A, B, C, D>(final ISO<A, B> ab, final ISO<C, D> cd) =>
    new ISO((Either l) => l.pm((a) => Either.left(ab.fw(a)), (c) => Either.right(cd.fw(c))), (Either r) => r.pm((b) => Either.left(ab.bw(b)), (d) => Either.right(cd.bw(d))));

ISO<Either<List<Null>, Null>, Either<List<Null>, Void>> isoEU() =>
    new ISO((Either le) => le.pm((l) => Either.left(l..insert(0, l)), (r) => Either.left([])),
            (Either re) => re.pm((l) => l.isNotEmpty ? Either.left(l..removeAt(0)) : Either.right(null), (r) => r.absurd()));

/// Going another way is hard (and is generally impossible)
/// Remember, for all valid ISO, converting and converting back
/// is the same as the original value.
/// You need this to prove some case are impossible.
ISO<A, B> isoUnOptional<A, B>(final ISO<Optional<A>, Optional<B>> iso) =>
    new ISO((a) => iso.fw(Optional.from(a)).orElseGet(() => iso.fw(Optional.empty()).get()), (b) => iso.bw(Optional.from(b)).orElseGet(() => iso.bw(Optional.empty()).get()));

/// hint: Function<A, C>, Function<B, D>
ISO<Function, Function> isoFunc<A, B, C, D>(final ISO<A, B> ab, final ISO<C, D> cd) =>
    new ISO((ac) => (a) => cd.fw(ac(ab.bw(a))), (bd) => (b) => cd.bw(bd(ab.fw(b))));

/// And we have isomorphism on isomorphism!
ISO<ISO<A, B>, ISO<B, A>> isoSymm<A, B>() => new ISO(symm, symm);

///  *** MENTION ***  ///
///  paste your code  ///
/// from isomorphism  ///
///  *** MENTION ***  ///

/// Sometimes, we can treat a Type as a Number:
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
ISO<Tuple<A, C>, Tuple<B, D>> isoProd<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd) => isoTuple(ab, cd);

/// a = b => c = d => a + c = b + d
ISO<Either<A, C>, Either<B, D>> isoPlus<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd) => isoEither(ab, cd);

/// a = b => S a = S b
ISO<Optional<A>, Optional<B>> isoS<A, B>(ISO<A, B> iso) => isoOptional(iso);

/// a = b => c = d => c ^ a = d ^ b
ISO<Function, Function> isoPow<A, B, C, D>(ISO<A, B> ab, ISO<C, D> cd) => isoFunc(ab, cd);

/// a + b = b + a
ISO<Either<A, B>, Either<B, A>> plusComm<A, B>() =>
    new ISO((ab) => ab.pm(Either.right, Either.left), (ba) => ba.pm(Either.right, Either.left));

/// a + b + c = a + (b + c)
ISO<Either<Either<A, B>, C>, Either<A, Either<B, C>>> plusAssoc<A, B, C>() => new ISO(         
        (abc) => abc.pm((ab) => ab.pm(Either.left, (b) => Either.right(Either.left(b))), (c) => Either.right(Either.right(c))), 
        (abc) => abc.pm((a) => Either.left(Either.left(a)), (bc) => bc.pm((b) => Either.left(Either.right(b)), Either.right)));

/// a * b = b * a
ISO<Tuple<A, B>, Tuple<B, A>> multComm<A, B>() => new ISO((ab) => new Tuple(ab.b, ab.a), (ba) => new Tuple(ba.b, ba.a));

/// a * b * c = a * (b * c)
ISO<Tuple<Tuple<A, B>, C>, Tuple<A, Tuple<B, C>>> multAssoc<A, B, C>() =>
    new ISO((a) => new Tuple(a.a.a, new Tuple(a.a.b, a.b)), (a) => new Tuple(new Tuple(a.a, a.b.a), a.b.b));

/// a * (b + c) = a * b + a * c
ISO<Tuple<A, Either<B, C>>, Either<Tuple<A, B>, Tuple<A, C>>> dist<A, B, C>() => new ISO(
        (abc) => abc.b.pm((b) => Either.left(new Tuple(abc.a, b)), (c) => Either.right(new Tuple(abc.a, c))),
        (abac) => abac.pm((ab) => new Tuple(ab.a, Either.left(ab.b)), (ac) => new Tuple(ac.a, Either.right(ac.b))));

/// (c ^ b) ^ a = c ^ (a * b)
/// Function<A, Function<B, C>>, Function<Tuple<A, B>, C>
ISO<Function, Function> curryISO<A, B, C>() =>
    new ISO((a) => (ab) => a(ab.a)(ab.b), (ab) => (a) => (b) => ab(new Tuple(a, b)));

/// 1 = S O (we are using peano arithmetic)
/// https://en.wikipedia.org/wiki/Peano_axioms
ISO<Unit, Optional<Void>> one() => new ISO((ignored) => Optional.empty(), (ignored) => Unit.INSTANCE);

/// 2 = S (S O)
ISO<bool, Optional<Optional<Void>>> two() =>
    new ISO((bool b) => b ? Optional.from(Optional.empty()) : Optional.empty(), Optional.hasValue);

/// 0 + b = b
ISO<Either<Void, B>, B> plusO<B>() => new ISO((vb) => vb.pm(Void.absurd, (b) => b), Either.right);

/// S a + b = S (a + b)
ISO<Either<Optional<A>, B>, Optional<Either<A, B>>> plusS<A, B>() => new ISO(
        (oab) => oab.pm((oa) => oa.map((a) => Optional.from(Either.left(a))).orElseGet(() => Optional.empty()), (b) => Optional.from(Either.right(b))), 
        (oab) => oab.map((ab) => ab.pm((a) => Either.left(Optional.from(a)), Either.right)).orElseGet(() => Either.left(Optional.empty())));

/// 1 + b = S b
ISO<Either<Unit, B>, Optional<B>> plusSO<B>() => trans(isoPlus(one(), refl()), trans(plusS(), isoS(plusO())));

/// 0 * a = 0
ISO<Tuple<Void, A>, Void> multO<A>() => new ISO((a) => a.a, Void.absurd);

/// S a * b = b + a * b
ISO<Tuple<Optional<A>, B>, Either<B, Tuple<A, B>>> multS<A, B>() => new ISO(
        (oab) => oab.a.map((a) => Either.right(new Tuple(a, oab.b))).orElseGet(() => Either.left(oab.b)),
        (bab) => bab.pm((b) => new Tuple(Optional.empty(), b), (ab) => new Tuple(Optional.from(ab.a), ab.b)));

/// S a * b = b + a * b
ISO<Tuple<Unit, B>, B> multSO<B>() => trans(isoProd(one(), refl()), trans(multS(), trans(isoPlus(refl(), multO()), trans(plusComm(), plusO()))));

/// a ^ 0 = 1
/// Function<Void, A>
ISO<Function, Unit> powO<A>() => new ISO((ignored) => Unit.INSTANCE, (unit) => Void.absurd);

/// a ^ (S b) = a * (a ^ b)
/// Function<Optional<B>, A>, Tuple<A, Function<B, A>>
ISO<Function, Tuple<A, Function>> powS<A, B>() => new ISO(
        (func) => new Tuple(func(Optional.empty()), (o) => func(Optional.from(o))),
        (tuple) => (b) => b.map(tuple.b).orElseGet(() => tuple.a));

/// a ^ 1 = a
/// Go the hard way (like multSO, plusSO)
/// to prove that you really get what is going on!
/// Function<Unit, A>
ISO<Function, A> powSO<A>() => trans(isoPow(one(), refl()), trans(powS(), trans(isoProd(refl(), powO()), trans(multComm(), multSO()))));
