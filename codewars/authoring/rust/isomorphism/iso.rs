#![allow(dead_code)]

/// so, when are two type, `a` and `b`, considered equal?
/// a definition might be, it is possible to go from `a` to `b`,
/// and from `b` to `a`.
/// Going a roundway trip should leave you the same value.
/// Unfortunately it is virtually impossible to test this in Haskell.
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

pub type ISO<A: 'static, B: 'static> = (Box<Fn(A) -> B>, Box<Fn(B) -> A>);

pub type IsoFL<A, B, C, D> = Box<FnOnce(Box<Fn(A) -> C>) -> Box<FnOnce(B) -> D>>;
pub type IsoFR<A, B, C, D> = Box<FnOnce(Box<Fn(B) -> D>) -> Box<FnOnce(A) -> C>>;
pub type IsoF<A, B, C, D> = (IsoFL<A, B, C, D>, IsoFR<A, B, C, D>);

pub fn iso<A: 'static, B: 'static, F1, F2>(a: F1, b: F2) -> ISO<A, B>
    where F1: 'static + Fn(A) -> B,
          F2: 'static + Fn(B) -> A,
{
    (Box::new(a), Box::new(b))
}

/// given ISO a b, we can go from a to b
pub fn sub_st_l<A, B>(iso: ISO<A, B>) -> Box<Fn(A) -> B> { iso.0 }

/// and vise versa
pub fn sub_st_r<A, B>(iso: ISO<A, B>) -> Box<Fn(B) -> A> { iso.1 }

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
        }, move |bd: Result<B, D>| match bd {
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
    }, move |re: Result<Vec<()>, Void>| match re {
        Ok(mut l) => if !l.is_empty() {
            l.remove(0);
            Ok(l)
        } else {
            Err(())
        },
        Err(r) => absurd(r),
    })
}

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

