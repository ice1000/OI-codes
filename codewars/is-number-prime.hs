module IsPrime where

import Data.List

-- ATTENTION: There's a bug in the test cases, which expects negative numbers
--            to return True if their absolute value is prime, e.g.
--            isPrime (-2) == True
--            isPrime (-3) == True
--            isPrime (-4) == False
-- Since the test cases cannot get changed at this point, take this bug into
-- account in your code.

mySqrt = floor . sqrt . fromIntegral

isPrime :: Integer -> Bool
isPrime 0    = False
isPrime 1    = False
isPrime (-1) = False
isPrime x'   = let x = abs x' in null [ a | a <- [2 .. mySqrt x], mod x a == 0 ]

