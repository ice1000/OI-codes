#![allow(dead_code)]

mod iso;

use iso::*;

const MOE: &'static str = "MOE";
const MEOW: &'static str = "MEOW";

fn lu() -> Vec<()> {
    vec![(), (), (), (), (), (), (), (), ()]
}

fn t_iso() -> ISO<bool, &'static str> {
    iso(move |x| if x { MEOW.clone() } else { MOE.clone() },
        move |x| MEOW == x)
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

#[test]
fn sub_st_l_test() {
    assert!(sub_st_l(iso_bool())(true));
    assert!(!sub_st_l(iso_bool())(false));
    assert!(sub_st_l(iso_bool_not())(false));
    assert!(MEOW == sub_st_l(t_iso())(true));
}

#[test]
fn sub_st_r_test() {
    assert!(sub_st_r(iso_bool())(true));
    assert!(!sub_st_r(iso_bool())(false));
    assert!(sub_st_r(t_iso())(MEOW));
}

#[test]
fn refl_test() {
    assert!(MEOW == sub_st_l(sub_st_l(refl())(t_iso()))(true));
}

#[test]
fn symm_test() {
    assert!(MEOW == sub_st_r(symm(t_iso()))(true));
}

#[test]
fn trans_test() {
    assert!(MEOW == sub_st_l(trans(refl(), trans(t_iso(), refl())))(true));
}

#[test]
fn iso_tuple_test() {
    assert!((MEOW, MOE) == sub_st_l(iso_tuple(t_iso(), t_iso()))((true, false)));
}

#[test]
fn iso_vec_test() {
    assert!(vec![MEOW, MEOW, MOE] == sub_st_l(iso_vec(t_iso()))(vec![true, true, false]));
}

#[test]
fn iso_func_test() {
    let (fun, _): (Box<_>, Box<_>) = iso_func(symm(t_iso()), t_iso());
    let _: Box<FnOnce(Box<Fn(_) -> _>) -> Box<FnOnce(_) -> _>> = fun;
}

#[test]
fn iso_option_test() {
    assert!(sub_st_l(iso_option(t_iso()))(None).is_none());
    assert!(Some(MEOW) == sub_st_l(iso_option(t_iso()))(Some(true)));
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
    assert!(Ok(false) == sub_st_l(iso_result(iso_bool_not(), t_iso()))(Ok(true)));
    assert!(Ok(true) == sub_st_l(iso_result(iso_bool_not(), t_iso()))(Ok(false)));
    assert!(Err(MEOW) == sub_st_l(iso_result(iso_bool_not(), t_iso()))(Err(true)));
}

#[test]
fn iso_symm_test() {
    assert!(MOE == sub_st_r(sub_st_r(iso_symm())(t_iso()))(false));
}

#[test]
fn iso_eu_test() {
    assert!(Ok(vec![]) == lrl(iso_eu(), Ok(vec![])));
    assert!(Ok(lu()) == lrl(iso_eu(), Ok(lu())));
    assert!(Err(()) == lrl(iso_eu(), Err(())));
    assert!(Ok(vec![]) == rlr(iso_eu(), Ok(vec![])));
    assert!(Ok(lu()) == rlr(iso_eu(), Ok(lu())));
    assert!(sub_st_l(iso_eu())(Err(())).is_ok());
}
