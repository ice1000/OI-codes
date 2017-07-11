module Divisors where

divisors :: Integral a => a -> Int
divisors x = length [ a | a <- [1..x], mod x a == 0 ]
