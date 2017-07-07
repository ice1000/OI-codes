module Codewars.Kata.LastFib where

fucker = 0 : 1 : (zipWith (\x y -> mod (x + y) 10) fucker $ tail fucker)

lastFibDigit :: Integer -> Int
lastFibDigit = (fucker !!) . fromInteger . (`mod` 9900)
