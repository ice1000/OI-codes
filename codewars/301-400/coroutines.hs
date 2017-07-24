{-# LANGUAGE DeriveFunctor #-}
module Coroutine where

import Control.Monad (ap, forever)
-- import Preloaded

-- | a =>> Done
-- | u =>> In
-- | d =>> Out
-- | r =>> Result
newtype Coroutine r u d a = Coroutine
  { runCoroutine :: (Command r u d a -> r) -> r } deriving (Functor)
--

data Command r u d a =
  Done a
  | Out d (Coroutine r u d a)
  | In (u -> Coroutine r u d a) deriving Functor
--

-- Useful alias
apply :: Coroutine r u d a -> (Command r u d a -> r) -> r
apply = runCoroutine
(=>>) = apply
(||>) = Out

instance Applicative (Coroutine r u d) where
  pure x = Coroutine ($ Done x)
  f <*> a = f >>= (<$> a)
--

instance Monad (Coroutine r u d) where
  return = pure
  (Coroutine f) >>= g = Coroutine $ \x -> f $ \(Done a) -> g a =>> x
--

(>>>) :: Coroutine r u m a -> Coroutine r m d a -> Coroutine r u d a
(Coroutine p1) >>> (Coroutine p2) = Coroutine $ \x -> x p1

-- It might be useful to define the following function
-- pipe2 :: Coroutine r u m a -> (m -> Coroutine r m d a) -> Coroutine r u d a

-- Library functions

output :: a -> Coroutine r u a ()
output v = Coroutine ($ v ||> pure ())

input :: Coroutine r v d v
input = Coroutine ($ In pure)

produce :: [a] -> Coroutine r u a ()
produce xs = undefined

consume :: Coroutine [t] u t a -> [t]
consume c = undefined

filterC :: (v -> Bool) -> Coroutine r v v ()
filterC p = undefined

limit :: Int -> Coroutine r v v ()
limit n = undefined

suppress :: Int -> Coroutine r v v ()
suppress n = undefined

add :: Coroutine r Int Int ()
add = undefined

duplicate :: Coroutine r v v ()
duplicate = undefined

-- Programs
-- 1. A program which outputs the first 5 even numbers of a stream.
-- 2. A program which produces a stream of the triangle numbers 
-- 3. A program which multiplies a stream by 2
-- 4. A program which sums adjacent pairs of integers

p1, p2, p3, p4 :: Coroutine r Int Int ()

p1 = undefined
p2 = undefined
p3 = undefined
p4 = undefined
