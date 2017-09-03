module Parsable where

import System.IO.Unsafe
import Data.Char

parses :: String -> Bool
parses [  '-'  ] = False
parses ('-' : s) = all isDigit s
parses [       ] = False
parses     s     = all isDigit s
