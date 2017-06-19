{-# OPTIONS_GHC #-}
module IPv4 where

import Data.Int (Int32)

type IPString = String

int32ToIP :: (Show a, Integral a) => a -> IPString
int32ToIP i' = let i = toInteger i' in
                 (show $ f $ div i 16777216)
       ++ "." ++ (show $ div (mod i 16777216) 65536)
       ++ "." ++ (show $ div (mod i 65536) 256)
       ++ "." ++ (show $ mod i 256)
  where f n = if n >= 0 then n else 256 + n
--
