module Fixit where

import Prelude hiding (reverse, foldr)

reverse' :: ([a] -> [a]) -> [a] -> [a]
reverse' _ [     ] = []
reverse' f (a : b) = f b ++ [a]

foldr' :: ((a -> b -> b) -> b -> [a] -> b) -> (a -> b -> b) -> b -> [a] -> b
foldr' _ _ o [     ] = o
foldr' f g o (a : b) = g a (f g o b)

