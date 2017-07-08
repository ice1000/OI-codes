module DigitalRoot where

digitalRoot :: Integral a => a -> a
digitalRoot x = let s = o x in if s < 10 then s else digitalRoot s

o :: Integral a => a -> a
o x
  |x < 10    = x
  |otherwise = mod x 10 + o (div x 10)
--
