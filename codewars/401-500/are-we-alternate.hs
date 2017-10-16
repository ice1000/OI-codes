module Kata.AreWeAlternate (isAlt) where

isAlt :: String -> Bool
isAlt [     ] = True
isAlt (a : b) = f b $ isV a
  where f (h : t) l = l /= isV h && (f t $ not l)
        f [     ] l = True
        isV = (`elem` "aeiou")
--

