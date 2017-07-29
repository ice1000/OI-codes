module Haskell.SylarDoom.MiniBitMove where

import Control.Monad

change '1' = '0'
change '0' = '1'

interpreter :: String -> String -> String
interpreter t a = f a $ join $ repeat t
  where
    f [     ]     _     = []
    f (a : b) ('0' : c) = a : f b c
    f (a : b) ('1' : c) = (change a : b) `f` c
    f theList [       ] = theList
--

