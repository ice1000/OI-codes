module Combinations where

import Control.Monad (filterM)

powerSet = filterM $ const [True, False]

combinations :: Int -> [a] -> [[a]]
combinations n l = [ a | a <- powerSet l, length a == n ]
