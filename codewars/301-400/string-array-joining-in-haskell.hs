module JoinedWords where

import Control.Monad

joinS :: [[Char]] -> [Char] -> [Char]
joinS p s = case join $ (s ++) <$> p of
  [] -> []
  ls -> length s `drop` ls
--
