module Codewars.NumberClimber where

climb :: Int -> [Int]
climb 1 = [1]
climb x = climb (div x 2) ++ [x]
