/// so, when are two type, `a` and `b`, considered equal?
/// a definition might be, it is possible to go from `a` to `b`,
/// and from `b` to `a`.
/// Going a roundway trip should leave you the same value.
/// Unfortunately it is virtually impossible to test this in Haskell.
/// This is called ISO.
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
  dynamic get();
  static _Left<L, R> left<L, R>(L l) => new _Left(l);
  static _Right<L, R> right<L, R>(R r) => new _Right(r);
  static isLeft(Either e) => e is _Left;
  static isRight(Either e) => e is _Right;
}

class _Left<L, R> extends Either<L, R> {
  L _l;
  _Left(this._l);
  @override dynamic get() => _l;
  @override T pm<T>(Function lt, Function rt) => lt(_l);
  @override bool operator ==(Object rhs) => (rhs as Either<L, R>).pm((o) => _l == o, (rr) => false);
}

class _Right<L, R> extends Either<L, R> {
  L _r;
  _Right(this._r);
  @override dynamic get() => _r;
  @override T pm<T>(Function lt, Function rt) => rt(_r);
  @override bool operator ==(Object rhs) => (rhs as Either<L, R>).pm((ll) => false, (o) => _r == o);
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
  @override bool operator ==(other);
  Optional<T> map(Function f);
  Optional<T> fmap(Function f);
  T get();
  T orElseGet(Function f);
  bool isPresent();
}

class _Some<T> extends Optional<T> {
  T _obj;
  _Some(this._obj);
  @override _Some<T> map(Function f) => new _Some(f(_obj));
  @override Optional<T> fmap(Function f) => f(_obj);
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
  A absurd<A>();
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
