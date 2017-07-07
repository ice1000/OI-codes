module Codewars.Numbers where

fucker = 0 : 1 : (zipWith (\x y -> mod (x + y) 10) fucker $ tail fucker)

getLastDigit :: Int -> Int
getLastDigit = (fucker !!) . (`mod` 9900)
