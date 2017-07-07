#![allow(dead_code)]

mod iso;

use iso::*;

fn moe() -> String {
    "MOE".to_string()
}

fn meow() -> String {
    "MEOW".to_string()
}

fn verbose() -> String {
    "It was me, DIO!".to_string()
}

fn cur(i: usize, b: bool) -> String {
    format!("{} {}", i, b)
}

fn cul(tuple: (usize, bool)) -> String {
    let (i, b) = tuple;
    cur(i, b)
}

fn lu() -> Vec<()> {
    vec![(), (), (), (), (), (), (), (), ()]
}

fn t_iso() -> ISO<bool, String> {
    iso(move |x| if x { meow().clone() } else { moe().clone() },
        move |x| meow() == x)
}

fn m_iso() -> ISO<Option<bool>, Option<bool>> {
    iso(move |it: Option<bool>| it
        .map(|b| if b { Some(false) } else { None })
        .unwrap_or(Some(true)),
        move |it: Option<bool>| it)
}

fn b_iso() -> ISO<bool, bool> {
    iso_un_option(m_iso())
}

fn bad_m_iso() -> ISO<Option<bool>, Option<bool>> {
    iso(move |it: Option<bool>| it
        .and_then(|b| if b { Some(false) } else { None }),
        move |it: Option<bool>| it)
}

fn bad_iso() -> ISO<bool, bool> {
    iso_un_option(bad_m_iso())
}

fn lrl<A: 'static, B: 'static>(i: ISO<A, B>, a: A) -> A {
    let (fw, bw) = i;
    bw(fw(a))
}

fn rlr<A: 'static, B: 'static>(i: ISO<A, B>, b: B) -> B {
    let (fw, bw) = i;
    fw(bw(b))
}

pub fn mult_so_<B: 'static>() -> ISO<((), B), B> {
    trans(iso_prod(one(), refl()),
          trans(mult_s(),
                trans(iso_plus(refl(), mult_o()),
                      trans(plus_comm(), plus_o()))))
}

pub fn plus_so_<B: 'static>() -> ISO<Result<(), B>, Option<B>> {
    trans(iso_plus(one(), refl()),
          trans(plus_s(), iso_s(plus_o())))
}

fn func(i: usize) -> String {
    vec!["DAZE".to_string(); i].join("")
}

fn mfunc(oi: Option<usize>) -> String {
    oi.map(func).unwrap_or(verbose())
}

#[test]
fn sub_st_l_test() {
    assert!(sub_st_l(iso_bool())(true));
    assert!(!sub_st_l(iso_bool())(false));
    assert!(sub_st_l(iso_bool_not())(false));
    assert!(meow() == sub_st_l(t_iso())(true));
}

#[test]
fn sub_st_r_test() {
    assert!(sub_st_r(iso_bool())(true));
    assert!(!sub_st_r(iso_bool())(false));
    assert!(sub_st_r(t_iso())(meow()));
}

#[test]
fn refl_test() {
    assert_eq!(meow(), sub_st_l(sub_st_l(refl())(t_iso()))(true));
}

#[test]
fn symm_test() {
    assert_eq!(meow(), sub_st_r(symm(t_iso()))(true));
}

#[test]
fn trans_test() {
    assert_eq!(meow(), sub_st_l(trans(refl(), trans(t_iso(), refl())))(true));
}

#[test]
fn iso_tuple_test() {
    assert_eq!((meow(), moe()), sub_st_l(iso_tuple(t_iso(), t_iso()))((true, false)));
}

#[test]
fn iso_vec_test() {
    assert_eq!(vec![meow(), meow(), moe()], sub_st_l(iso_vec(t_iso()))(vec![true, true, false]));
}

#[test]
fn iso_func_test() {
    let (fun, _): (Box<_>, Box<_>) = iso_func(symm(t_iso()), t_iso());
    let _: Box<FnOnce(Box<Fn(_) -> _>) -> Box<FnOnce(_) -> _>> = fun;
}

#[test]
fn iso_option_test() {
    assert!(sub_st_l(iso_option(t_iso()))(None).is_none());
    assert!(Some(meow()) == sub_st_l(iso_option(t_iso()))(Some(true)));
}

#[test]
fn iso_un_option_test() {
    assert!(!sub_st_l(b_iso())(true));
    assert!(sub_st_l(b_iso())(false));
    assert!(!sub_st_l(bad_iso())(true));
}

#[test]
#[should_panic]
fn iso_un_option_test_last() {
    sub_st_l(bad_iso())(false);
}

#[test]
fn iso_result_test() {
    assert_eq!(Ok(false), sub_st_l(iso_result(iso_bool_not(), t_iso()))(Ok(true)));
    assert_eq!(Ok(true), sub_st_l(iso_result(iso_bool_not(), t_iso()))(Ok(false)));
    assert_eq!(Err(meow()), sub_st_l(iso_result(iso_bool_not(), t_iso()))(Err(true)));
}

#[test]
fn iso_symm_test() {
    assert_eq!(moe(), sub_st_r(sub_st_r(iso_symm())(t_iso()))(false));
}

#[test]
fn iso_eu_test() {
    assert_eq!(Ok(vec![]), lrl(iso_eu(), Ok(vec![])));
    assert!(Ok(lu()) == lrl(iso_eu(), Ok(lu())));
    assert_eq!(Err(()), lrl(iso_eu(), Err(())));
    assert!(Ok(vec![]) == rlr(iso_eu(), Ok(vec![])));
    assert!(Ok(lu()) == rlr(iso_eu(), Ok(lu())));
    assert!(sub_st_l(iso_eu())(Err(())).is_ok());
}

#[test]
fn assoc_test() {
    assert_eq!(Ok::<Result<i16, bool>, String>(Ok(233)),
               lrl(plus_assoc(), Ok::<Result<i16, bool>, String>(Ok(233))));
    assert_eq!(Ok::<Result<i16, bool>, String>(Err(true)),
               lrl(plus_assoc(), Ok::<Result<i16, bool>, String>(Err(true))));
    assert_eq!(Err::<Result<i16, bool>, String>(verbose()),
               lrl(plus_assoc(), Err::<Result<i16, bool>, String>(verbose())));
    assert_eq!(Ok::<i16, Result<bool, String>>(233),
               rlr(plus_assoc(), Ok::<i16, Result<bool, String>>(233)));
    assert_eq!(Err::<i16, Result<bool, String>>(Ok(true)),
               rlr(plus_assoc(), Err::<i16, Result<bool, String>>(Ok(true))));
    assert_eq!(Err::<i16, Result<bool, String>>(Err(verbose())),
               rlr(plus_assoc(), Err::<i16, Result<bool, String>>(Err(verbose()))));
}

#[test]
fn dist_test() {
    assert_eq!((233, Ok::<bool, String>(true)),
               lrl(dist(), (233, Ok::<bool, String>(true))));
    assert_eq!((233, Err::<bool, String>(verbose())),
               lrl(dist(), (233, Err::<bool, String>(verbose()))));
    assert_eq!(Ok::<(i16, bool), (i16, String)>((0, true)),
               rlr(dist(), Ok::<(i16, bool), (i16, String)>((0, true))));
    assert_eq!(Err::<(i16, bool), (i16, String)>((0, verbose())),
               rlr(dist(), Err::<(i16, bool), (i16, String)>((0, verbose()))));
}

#[test]
fn one_test() {
    assert_eq!((), lrl(one(), ()));
    assert!(None == rlr(one(), None));
}

#[test]
fn two_test() {
    assert!(lrl(two(), true));
    assert!(!lrl(two(), false));
    assert!(None == rlr(two(), None));
    assert!(Some(None) == rlr(two(), Some(None)));
}

#[test]
fn plus_test() {
    assert!(Err(verbose()) == lrl(plus_o(), Err(verbose())));
    assert!(verbose() == rlr(plus_o(), verbose()));
    assert_eq!(Ok::<Option<String>, i16>(Some(verbose())),
               lrl(plus_s(), Ok::<Option<String>, i16>(Some(verbose()))));
    assert_eq!(Ok::<Option<String>, i16>(None),
               lrl(plus_s(), Ok::<Option<String>, i16>(None)));
    assert_eq!(Err::<Option<String>, i16>(233),
               lrl(plus_s(), Err::<Option<String>, i16>(233)));
    assert_eq!(Some::<Result<String, i16>>(Ok(verbose())),
               rlr(plus_s(), Some::<Result<String, i16>>(Ok(verbose()))));
    assert_eq!(Some::<Result<String, i16>>(Err(233)),
               rlr(plus_s(), Some::<Result<String, i16>>(Err(233))));
    assert_eq!(None::<Result<String, i16>>,
               rlr(plus_s(), None::<Result<String, i16>>));
    assert_eq!(Ok::<(), i16>(()), lrl(plus_so_(), Ok::<(), i16>(())));
    assert_eq!(Err::<(), i16>(233), lrl(plus_so_(), Err::<(), i16>(233)));
    assert_eq!(None::<i16>, rlr(plus_so_(), None::<i16>));
    assert_eq!(Some(233), rlr(plus_so_(), Some(233)));
}

#[test]
fn mult_test() {
    assert_eq!((Some(verbose()), 233), lrl(mult_s(), (Some(verbose()), 233)));
    assert_eq!((None::<()>, 233), lrl(mult_s(), (None::<()>, 233)));
    assert_eq!(Ok::<i16, (String, i16)>(233),
               rlr(mult_s(), Ok::<i16, (String, i16)>(233)));
    assert_eq!(Err::<i16, (String, i16)>((verbose(), 233)),
               rlr(mult_s(), Err::<i16, (String, i16)>((verbose(), 233))));
    assert_eq!(((), true), lrl(mult_so_(), ((), true)));
    assert_eq!(((), false), lrl(mult_so_(), ((), false)));
    assert!(rlr(mult_so_(), true));
    assert!(!rlr(mult_so_(), false));
}

#[test]
fn pow_test() {
    /// checked all the types
    let (l, r): (Box<_>, Box<_>) = pow_o::<()>();
    let _: Box<FnOnce(Box<Fn(Void) -> ()>) -> ()> = l;
    let _: Box<FnOnce(()) -> Box<FnOnce(Void) -> ()>> = r;
    let (l, r): (Box<_>, Box<_>) = pow_s::<(), ()>();
    let _: Box<FnOnce(Box<Fn(Option<()>) -> ()>) -> ((), Box<FnOnce(()) -> ()>)> = l;
    let _: Box<FnOnce(((), Box<Fn(()) -> ()>)) -> Box<FnOnce(Option<()>) -> ()>> = r;
    let (l, r): (Box<_>, Box<_>) = pow_so::<()>();
    let _: Box<FnOnce(Box<Fn(()) -> ()>) -> ()> = l;
    let _: Box<FnOnce(()) -> Box<FnOnce(()) -> ()>> = r;
}

#[test]
fn curry_test() {
    let (l, r): (Box<_>, Box<_>) = curry_iso::<(), (), ()>();
    let _: Box<FnOnce(Box<Fn(()) -> Box<Fn(()) -> ()>>) ->
               Box<FnOnce(((), ())) -> ()>> = l;
    let _: Box<FnOnce(Box<Fn(((), ())) -> ()>) ->
               Box<FnOnce(()) -> Box<FnOnce(()) -> ()>>> = r;
    // (Box::new(move |a| Box::new(move |b| cur(a, b))));
}
