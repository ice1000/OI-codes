module Codewars.Kata.FactorialTail where

import Data.List (group)
import Control.Arrow ((&&&))

zeroes :: Integral a => a -> a -> a
zeroes base n = minimum . ((f . (head &&& length)) <$>) . group . pd $ base
    where f (a, b) = (`div` fromIntegral b) . sum . ((n `div`) <$>) $ [a ^ i | i <- [1 .. floor (fromIntegral a `logBase` fromIntegral n)]]
          pd x | x == 1 = [ ]
               | null d = [x]
               | True   = head d : pd (div x $ head d)
               where d = filter ((== 0) . (x `mod`)) [2 .. floor $ sqrt $ fromIntegral $ x]
--

