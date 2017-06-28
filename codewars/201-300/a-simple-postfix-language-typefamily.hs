{-# LANGUAGE
    TypeFamilies
  , FlexibleContexts
  , FlexibleInstances
  , UndecidableInstances
  , MultiParamTypeClasses
  , NoMonomorphismRestriction
  #-}

module Postfix where

data Add = Add
data Push = Push
data End = End

class Cmd stk res where
  exec :: stk -> res
--

instance (a ~ Int, s ~ (v, Int)) => Cmd s (End -> a) where
  exec a _ = snd a
--

instance (a ~ Int, Cmd (s, Int) res) => Cmd s (Push -> a -> res) where
  exec s _ n = exec (s, n)
--

instance Cmd (s, Int) res => Cmd ((s, Int), Int) (Add -> res) where
  exec (n, m) _ = exec (fst n, snd n + m)
--

begin = exec ()
push  = Push
add = Add
end = End
