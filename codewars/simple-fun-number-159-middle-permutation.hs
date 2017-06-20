module MiddlePermutation.JorgeVS.Kata where

middlePermutation :: String -> String
middlePermutation s
  |elem l [0, 2] = s
  |even l        = let m = s !! (div l 2 - 1) in
     m : reverse [ c | c <- s, c /= m ]
  |otherwise     = let mi = div l 2 in let
     c1 = s !! mi
     c2 = s !! (mi - 1) in
     c1 : c2 : reverse [ c | c <- s, c /= c1, c /= c2 ]
  where l = length s
--
