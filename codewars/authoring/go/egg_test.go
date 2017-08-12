package kata_test

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
	. "codewarrior/kata"
	"time"
	"math/rand"
	"math/big"
)

func mul(x, y *big.Int) *big.Int {
	return big.NewInt(0).Mul(x, y)
}

func add(x, y *big.Int) *big.Int {
	return big.NewInt(0).Add(x, y)
}

func sub(x, y *big.Int) *big.Int {
	return big.NewInt(0).Sub(x, y)
}

func div(x, y *big.Int) *big.Int {
	return big.NewInt(0).Div(x, y)
}

func height(n, m *big.Int) *big.Int {
  if n.Cmp(big.NewInt(0)) == 0 || m.Cmp(big.NewInt(0)) == 0 {
		return big.NewInt(0)
	}
  if n.Cmp(m) > 0 {
		n = m
	}
  c := big.NewInt(1)
  b := big.NewInt(1)
  a := big.NewInt(0)
  for c.Cmp(n) <= 0 {
    d := div(mul(sub(add(m, big.NewInt(1)), c), b), c)
    c = add(c, big.NewInt(1))
    b = d
    a = add(a, d)
  }
  return a
}

func testerInt(a, b, c int64) {
	Expect(Height(big.NewInt(a), big.NewInt(b)).Cmp(big.NewInt(c))).To(Equal(0))
}

func testerBig(a, b, c string) {
	x := new(big.Int)
	x.SetString(a, 0)
	y := new(big.Int)
	y.SetString(b, 0)
	z := new(big.Int)
	z.SetString(c, 0)
	Expect(Height(x, y).Cmp(z)).To(Equal(0))
}

func r() int64 {
	return int64(rand.Intn(20000))
}

func ok(a, b string) {
	x := new(big.Int)
	x.SetString(a, 0)
	y := new(big.Int)
	y.SetString(b, 0)
	Expect(Height(x, y).Cmp(height(x, y))).To(Equal(0))
}

func veryOk(a, b int64) {
	Expect(Height(big.NewInt(a), big.NewInt(b)).Cmp(height(big.NewInt(a), big.NewInt(b)))).To(Equal(0))
}

var _ = Describe("Should work", func() {
	It("should work for some basic tests", func() {
		testerInt(1, 51, 51)
		testerInt(2, 1, 1)
		testerInt(4, 17, 3213)
		testerInt(16, 19, 524096)
		testerInt(23, 19, 524287)
	})
	It("should work for some advanced tests", func() {
		testerBig("13", "550", "60113767426276772744951355")
		testerBig("271", "550", "1410385042520538326622498273346382708200418583791594039531058458108130216985983794998105636900856496701928202738750818606797013840207721579523618137220278767326000095")
		testerBig("531", "550", "3685510180489786476798393145496356338786055879312930105836138965083617346086082863365358130056307390177215209990980317284932211552658342317904346433026688858140133147")
	})
	It("should work for some serious tests :)", func() {
		ok("311", "10131")
		ok("6511", "11731")
		ok("11111", "12911")
		ok("99999", "13911")
	})
	It("should work for some random tests :)", func() {
		rand.Seed(time.Now().UTC().UnixNano())
		veryOk(r(), r())
		veryOk(r(), r())
		veryOk(r(), r())
	})
})
