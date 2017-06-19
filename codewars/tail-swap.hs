module Kata(tailSwap) where

import Data.List.Split

tailSwap :: (String, String) -> (String, String)
tailSwap (a, b) = let (a1 : (a2 : _)) = splitOn ":" a
                      (b1 : (b2 : _)) = splitOn ":" b in
  (a1 ++ ":" ++ b2, b1 ++ ":" ++ a2)
--

