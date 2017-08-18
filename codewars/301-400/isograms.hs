module Isogram where

import Data.Char
import Data.List

isIsogram :: String -> Bool
isIsogram s = let x = toLower <$> s in length (nub x) == length x
