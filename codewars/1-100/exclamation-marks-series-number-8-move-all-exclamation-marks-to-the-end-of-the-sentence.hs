module Kata (remove) where

remove :: String -> String
remove s = [ c | c <- s, c /= '!' ] ++ [ c | c <- s, c == '!' ]
