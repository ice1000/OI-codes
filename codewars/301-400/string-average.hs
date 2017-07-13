module Kata.StringAverage (averageString) where

import Data.List.Split

change "zero"  = 0
change "one"   = 1
change "two"   = 2
change "three" = 3
change "four"  = 4
change "five"  = 5
change "six"   = 6
change "seven" = 7
change "eight" = 8
change "nine"  = 9
change "ten"   = 10
change _       = -1

rechange 0    = "zero"
rechange 1    = "one"
rechange 2    = "two"
rechange 3    = "three"
rechange 4    = "four"
rechange 5    = "five"
rechange 6    = "six"
rechange 7    = "seven"
rechange 8    = "eight"
rechange 9    = "nine"
rechange 10   = "ten"
rechange _    = "n/a"

avg :: [Int] -> Int
avg ls
  |(-1) `elem` ls = -1
  |otherwise      = sum ls `div` length ls
--

averageString :: String -> String
averageString = rechange . avg . (change <$>) . splitOn " "
