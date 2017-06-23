module Codewars.Kata.VampireNumbers where

import Data.List

isVampire :: Integer -> Integer -> Bool
isVampire a b = let x = sort $ show a ++ show b
                    y = sort $ show $ a * b in
  x == y
--
