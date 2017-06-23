module FindUniqueDouble.JorgeVS.Kata where

import Data.List

findUnique :: [Double] -> Double
findUnique x = find $ sort x
  where find [      x      ] = x
        find (x1 : (x2 : xs))
          |x1 /= x2   = x1
          |otherwise  = find $ dropWhile (== x1) xs
--

