package kata

import (
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

func Height(n, m *big.Int) *big.Int {
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
