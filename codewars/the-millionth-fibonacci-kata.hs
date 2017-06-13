module Fibonacci where

import Data.List
import Data.Bits

fibonacci :: Int -> Integer
fibonacci n = snd . foldl' fib' (1, 0) . dropWhile not $
  [testBit n k | k <- let s = finiteBitSize n in [s - 1, s - 2 .. 0]]
  where fib' (f, g) p
          |p         = (f * (f + 2 * g), ss)
          |otherwise = (ss, g * (2 * f - g))
          where ss = f * f + g * g
--

fib :: Integer -> Integer
fib n
  |n >= 0       = fibonacci $ fromInteger n
  |mod n 2 == 1 = fibonacci $ (0 - fromInteger n)
  |otherwise    = 0 - fibonacci (0 - fromInteger n)
--

