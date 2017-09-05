module Pangram where

import Data.Char

isPangram :: String -> Bool
isPangram ss = all (`elem` (toLower <$> ss)) [ 'a' .. 'z' ]
