#![allow(dead_code)]

/// so, when are two type, `a` and `b`, considered equal?
/// a definition might be, it is possible to go from `a` to `b`,
/// and from `b` to `a`.
/// Going a roundway trip should leave you the same value.
/// Unfortunately it is virtually impossible to test this in Haskell,
/// neither in Rust.
/// This is called ISO.
pub enum Void { }

impl PartialEq for Void {
    fn eq(&self, _: &Void) -> bool {
        true
    }
}

pub fn absurd(_: Void) -> ! {
    panic!("You must be kidding! Where did you find that void instance?");
}

pub type Func<A, B> = Box<Fn(A) -> B>;
pub type RetFunc<A, B> = Box<FnOnce(A) -> B>;
pub type ISO<A: 'static, B: 'static> = (Func<A, B>, Func<B, A>);

pub fn iso<A: 'static, B: 'static, F1, F2>(a: F1, b: F2) -> ISO<A, B>
    where F1: 'static + Fn(A) -> B,
          F2: 'static + Fn(B) -> A,
{
    (Box::new(a), Box::new(b))
}

/// given ISO a b, we can go from a to b
pub fn sub_st_l<A, B>(iso: ISO<A, B>) -> Func<A, B> { iso.0 }

/// and vise versa
pub fn sub_st_r<A, B>(iso: ISO<A, B>) -> Func<B, A> { iso.1 }

/// There can be more than one ISO a b
pub fn iso_bool() -> ISO<bool, bool> {
    refl()
}

pub fn iso_bool_not() -> ISO<bool, bool> {
    iso(|b: bool| !b, |b: bool| !b)
}

/// isomorphism is reflexive
pub fn refl<A: 'static>() -> ISO<A, A> {
    iso(|a| a, |a| a)
}

/// isomorphism is symmetric
pub fn symm<A: 'static, B: 'static>(i: ISO<A, B>) -> ISO<B, A> {
    let (f, b) = i;
    iso(move |x| b(x), move |x| f(x))
}

/// isomorphism is transitive
pub fn trans<A: 'static, B: 'static, C: 'static>
    (ab: ISO<A, B>, bc: ISO<B, C>) -> ISO<A, C> {
        let (a2b, b2a) = ab;
        let (b2c, c2b) = bc;
        iso(move |a| b2c(a2b(a)), move |c| b2a(c2b(c)))
    }

/// we can combine isomorphism
pub fn iso_tuple<A: 'static, B: 'static, C: 'static, D: 'static>
    (ab: ISO<A, B>, cd: ISO<C, D>) -> ISO<(A, C), (B, D)> {
        let (a2b, b2a) = ab;
        let (c2d, d2c) = cd;
        iso(move |(a, c)| (a2b(a), c2d(c)), move |(b, d)| (b2a(b), d2c(d)))
    }

pub fn iso_vec<A: 'static, B: 'static>(i: ISO<A, B>) -> ISO<Vec<A>, Vec<B>> {
    let (fw, bw) = i;
    iso(move |a: Vec<A>| a.into_iter().map(|x| fw(x)).collect(),
        move |b: Vec<B>| b.into_iter().map(|y| bw(y)).collect())
}

pub fn iso_option<A: 'static, B: 'static>
    (i: ISO<A, B>) -> ISO<Option<A>, Option<B>> {
        let (fw, bw) = i;
        iso(move |a: Option<A>| a.map(|x| fw(x)),
            move |b: Option<B>| b.map(|x| bw(x)))
    }

pub fn iso_result<A: 'static, B: 'static, C: 'static, D: 'static>
    (ab: ISO<A, B>, cd: ISO<C, D>) -> ISO<Result<A, C>, Result<B, D>> {
        let (a2b, b2a) = ab;
        let (c2d, d2c) = cd;
        iso(move |ac: Result<A, C>| match ac {
            Ok(a) => Ok(a2b(a)),
            Err(c) => Err(c2d(c)),
        },  move |bd: Result<B, D>| match bd {
            Ok(b) => Ok(b2a(b)),
            Err(d) => Err(d2c(d)),
        })
    }

/// Going another way is hard (and is generally impossible)
/// Remember, for all valid ISO, converting and converting back
/// is the same as the original value.
/// You need this to prove some case are impossible.
pub fn iso_un_option<A: 'static, B: 'static>
    (i: ISO<Option<A>, Option<B>>) -> ISO<A, B> {
        let (fw, bw) = i;
        iso(move |a| fw(Some(a)).unwrap_or_else(|| fw(None).unwrap()),
            move |b| bw(Some(b)).unwrap_or_else(|| bw(None).unwrap()))
    }

pub fn iso_eu() -> ISO<Result<Vec<()>, ()>, Result<Vec<()>, Void>> {
    iso(move |le: Result<Vec<()>, ()>| match le {
        Ok(mut l) => {
            l.push(());
            Ok(l)
        },
        Err(_) => Ok(vec![]),
    },  move |re: Result<Vec<()>, Void>| match re {
        Ok(mut l) => if !l.is_empty() {
            l.remove(0);
            Ok(l)
        } else {
            Err(())
        },
        Err(r) => absurd(r),
    })
}

pub type IsoFL<A, B, C, D> = RetFunc<Func<A, C>, RetFunc<B, D>>;
pub type IsoFR<A, B, C, D> = RetFunc<Func<B, D>, RetFunc<A, C>>;
pub type IsoF<A, B, C, D> = (IsoFL<A, B, C, D>, IsoFR<A, B, C, D>);

/// translator note:
/// FnBox is not yet supported, we can only return an uncallable
/// Box<FnOnce> (RetFunc). You should return the function with
/// correct type, which will be checked by the tests.
pub fn iso_func<A: 'static, B: 'static, C: 'static, D: 'static>
    (ab: ISO<A, B>, cd: ISO<C, D>) -> IsoF<A, B, C, D> {
        let (a2b, b2a) = ab;
        let (c2d, d2c) = cd;
        
        (Box::new(move |ac: Box<Fn(A) -> C>| {
            Box::new(move |b| {
                let a = b2a(b);
                let c = ac(a);
                c2d(c)
            }) as Box<FnOnce(B) -> D>
        }), Box::new(move |bd: Box<Fn(B) -> D>| {
            Box::new(move |a| {
                let b = a2b(a);
                let d = bd(b);
                d2c(d)
            }) as Box<FnOnce(A) -> C>
        }))
    }

/// And we have isomorphism on isomorphism!
pub fn iso_symm<A: 'static, B: 'static>() -> ISO<ISO<A, B>, ISO<B, A>> {
    iso(symm, symm)
}

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
pub fn iso_prod<A: 'static, B: 'static, C: 'static, D: 'static>
    (ab: ISO<A, B>, cd: ISO<C, D>) -> ISO<(A, C), (B, D)> {
        iso_tuple(ab, cd)
    }

/// a = b => c = d => a + c = b + d
pub fn iso_plus<A: 'static, B: 'static, C: 'static, D: 'static>
    (ab: ISO<A, B>, cd: ISO<C, D>) -> ISO<Result<A, C>, Result<B, D>> {
        iso_result(ab, cd)
    }

/// a = b => S a = S b
pub fn iso_s<A: 'static, B: 'static>
    (i: ISO<A, B>) -> ISO<Option<A>, Option<B>> {
        iso_option(i)
    }

/// a = b => c = d => c ^ a = d ^ b
pub fn iso_pow<A: 'static, B: 'static, C: 'static, D: 'static>
    (ab: ISO<A, B>, cd: ISO<C, D>) -> IsoF<A, B, C, D> {
        iso_func(ab, cd)
    }

/// a + b = b + a
pub fn plus_comm<A: 'static, B: 'static>() -> ISO<Result<A, B>, Result<B, A>> {
    iso(|ab| match ab {
        Ok(o) => Err(o),
        Err(o) => Ok(o),
    },  |ba| match ba {
        Ok(o) => Err(o),
        Err(o) => Ok(o),
    })
}

/// a + b + c = a + (b + c)
pub fn plus_assoc<A: 'static, B: 'static, C: 'static>
    () -> ISO<Result<Result<A, B>, C>, Result<A, Result<B, C>>> {
        iso(|abc| match abc {
            Ok(Ok(a)) => Ok(a),
            Ok(Err(b)) => Err(Ok(b)),
            Err(c) => Err(Err(c)),
        },  |abc| match abc {
            Ok(a) => Ok(Ok(a)),
            Err(Ok(b)) => Ok(Err(b)),
            Err(Err(c)) => Err(c),
        })
    }

/// a * b = b * a
pub fn mult_comm<A: 'static, B: 'static>() -> ISO<(A, B), (B, A)> {
    iso(|(a, b)| (b, a), |(b, a)| (a, b))
}

/// a * b * c = a * (b * c)
pub fn mult_assoc<A: 'static, B: 'static, C: 'static>
    () -> ISO<((A, B), C), (A, (B, C))> {
        iso(|((a, b), c)| (a, (b, c)),
            |(a, (b, c))| ((a, b), c))
    }

/// a * (b + c) = a * b + a * c
pub fn dist<A: 'static, B: 'static, C: 'static>
    () -> ISO<(A, Result<B, C>), Result<(A, B), (A, C)>> {
    iso(|var| match var {
        (a, Ok(b)) => Ok((a, b)),
        (a, Err(c)) => Err((a, c)),
    },  |var| match var {
        Ok((a, b)) => (a, Ok(b)),
        Err((a, c)) => (a, Err(c)),
    })
}

pub type IsoCL<A, B, C> = RetFunc<Func<A, Func<B, C>>, RetFunc<(A, B), C>>;
pub type IsoCR<A, B, C> = RetFunc<Func<(A, B), C>, RetFunc<A, RetFunc<B, C>>>;
pub type IsoC<A, B, C> = (IsoCL<A, B, C>, IsoCR<A, B, C>);

/// translator note:
/// FnBox is not yet supported, we can only return an uncallable
/// Box<FnOnce> (RetFunc). You should return the function with
/// correct type, which will be checked by the tests.
/// later you'll have to implement three more functions that related
/// to `RetFunc`. enjoy!

/// (c ^ b) ^ a = c ^ (a * b)
pub fn curry_iso<A: 'static, B: 'static, C: 'static>() -> IsoC<A, B, C> {
    (Box::new(|f: Func<A, Func<B, C>>| Box::new(
        move |(a, b)| f(a)(b)) as RetFunc<(A, B), C>),
     Box::new(|f: Func<(A, B), C>| Box::new(move |a| Box::new(
         move |b| f((a, b))) as RetFunc<B, C>) as RetFunc<A, RetFunc<B, C>>
     ))
}

/// 1 = S O (we are using peano arithmetic)
/// https://en.wikipedia.org/wiki/Peano_axioms  
pub fn one() -> ISO<(), Option<Void>> {
    iso(|_| None, |_| ())
}

/// 2 = S (S O)
pub fn two() -> ISO<bool, Option<Option<Void>>> {
    iso(|b| if b { Some(None) } else { None }, |o| o.is_some())
}

/// 0 + b = b
pub fn plus_o<B: 'static>() -> ISO<Result<Void, B>, B> {
    iso(|res: Result<Void, B>| match res {
        Ok(v) => absurd(v),
        Err(b) => b,
    },  |b| Err(b))
}

/// S a + b = S (a + b)
pub fn plus_s<A: 'static, B: 'static>
    () -> ISO<Result<Option<A>, B>, Option<Result<A, B>>> {
        iso(|res: Result<Option<A>, B>| match res {
            Ok(None) => None,
            Ok(Some(a)) => Some(Ok(a)),
            Err(b) => Some(Err(b)),
        },  |opt: Option<Result<A, B>>| match opt {
            Some(Err(b)) => Err(b),
            Some(Ok(a)) => Ok(Some(a)),
            None => Ok(None),
        })
    }

/// 1 + b = S b
pub fn plus_so<B: 'static>() -> ISO<Result<(), B>, Option<B>> {
    trans(iso_plus(one(), refl()),
          trans(plus_s(), iso_s(plus_o())))
}

/// 0 * a = 0
pub fn mult_o<A: 'static>() -> ISO<(Void, A), Void> {
    iso(|(v, _)| v, |v| absurd(v))
}

/// S a * b = b + a * b
pub fn mult_s<A: 'static, B: 'static>
    () -> ISO<(Option<A>, B), Result<B, (A, B)>> {
        iso(|(opt, b)| match opt {
            Some(a) => Err((a, b)),
            None => Ok(b),
        },  |res| match res {
            Ok(b) => (None, b),
            Err((a, b)) => (Some(a), b),
        })
    }

/// S a * b = b + a * b
pub fn mult_so<B: 'static>() -> ISO<((), B), B> {
    trans(iso_prod(one(), refl()),
          trans(mult_s(),
                trans(iso_plus(refl(), mult_o()),
                      trans(plus_comm(), plus_o()))))
}

/// Here we go, the last three functions related to
/// RetFunc. They're easy!

pub type IsoPL<A> = RetFunc<Func<Void, A>, ()>;
pub type IsoPR<A> = RetFunc<(), RetFunc<Void, A>>;
pub type IsoP<A> = (IsoPL<A>, IsoPR<A>);

/// a ^ 0 = 1
pub fn pow_o<A: 'static>() -> IsoP<A> {
    (Box::new(|_| ()),
     Box::new(|_| Box::new(|v| absurd(v))))
}

pub type IsoPsL<A, B> = RetFunc<Func<Option<B>, A>, (A, RetFunc<B, A>)>;
pub type IsoPsR<A, B> = RetFunc<(A, Func<B, A>), RetFunc<Option<B>, A>>;
pub type IsoPs<A, B> = (IsoPsL<A, B>, IsoPsR<A, B>);

/// a ^ (S b) = a * (a ^ b)
pub fn pow_s<A: 'static, B: 'static>() -> IsoPs<A, B> {
    (Box::new(|f: Func<Option<B>, A>|
        (f(None), Box::new(
            move |o| f(Some(o))))),
     Box::new(|(a, f)| Box::new(
         move |opt| match opt {
             Some(o) => f(o),
             None => a,
         })))
}

pub type IsoPsoL<A> = RetFunc<Func<(), A>, A>;
pub type IsoPsoR<A> = RetFunc<A, RetFunc<(), A>>;
pub type IsoPso<A> = (IsoPsoL<A>, IsoPsoR<A>);

/// a ^ 1 = a
/// In Haskell/Java/Dart, you can go the hard way
/// (like mult_so, plus_so) to prove that you really get what is
/// going on.
/// Unfortunately, in Rust, you can only go the trivial way.
/// Because Rust doesn't support FnBox ATM.
pub fn pow_so<A: 'static>() -> IsoPso<A> {
    (Box::new(|f| f(())),
     Box::new(|a| Box::new(move |_| a)))
}
