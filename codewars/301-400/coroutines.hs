{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE LambdaCase #-}

module Coroutine where

import Control.Monad
import Preloaded

-- Preloaded contains the following:
--
-- newtype Coroutine r u d a = Coroutine { runCoroutine :: (Command r u d a -> r) -> r } deriving (Functor)

-- data Command r u d a =
--   Done a
--   | Out d (Coroutine r u d a)
--   | In (u -> Coroutine r u d a) deriving Functor

-- Useful alias
apply :: Coroutine r u d a -> (Command r u d a -> r) -> r
apply = runCoroutine

(||>) :: d -> Coroutine r u d a -> Command r u d a
(||>) = Out

(=>>) :: Coroutine r u d a -> (Command r u d a -> r) -> r
(=>>) = apply

instance Applicative (Coroutine r u d) where
  pure x  = Coroutine ($ Done x)
  f <*> a = f >>= (<$> a)
--

instance Monad (Coroutine r u d) where
  return = pure
  (Coroutine f) >>= g = Coroutine $ \k -> f $ \gg -> case gg of
    Done a  -> g a =>> k
    Out d c -> k $ Out d $ c >>= g
    In c    -> k $ In $ (>>= g) <$> c
--

(>>>) :: Coroutine r u m a -> Coroutine r m d a -> Coroutine r u d a
p'1 >>> (Coroutine p'2) = Coroutine $ \k -> p'2 $ \case
  Done a  -> k $ Done a
  Out d c -> k $ Out d $ p'1 >>> c
  In c    -> pipe2 p'1 c =>> k
--

-- It might be useful to define the following function

pipe2 :: Coroutine r u m a -> (m -> Coroutine r m d a) -> Coroutine r u d a
pipe2 (Coroutine p'1) p'2 = Coroutine $ \k -> p'1 $ \case
    Done a  -> k $ Done a
    Out d c -> c >>> p'2 d =>> k
    In c    -> k $ In $ (`pipe2` p'2) <$> c
--

-- Library functions

output :: a -> Coroutine r u a ()
output v = Coroutine ($ v ||> pure ())

input :: Coroutine r v d v
input = Coroutine ($ In pure)

produce :: [a] -> Coroutine r u a ()
produce =  mapM_ output

consume :: Coroutine [t] u t a -> [t]
consume (Coroutine x) = x $ \case
    Out d c -> d : consume c
    _       -> []
--

filterC :: (v -> Bool) -> Coroutine r v v ()
filterC p = forever $ input >>= \v -> p v `when` output v

limit :: Int -> Coroutine r v v ()
limit = flip replicateM_ $ input >>= output

suppress :: Int -> Coroutine r v v ()
suppress n = replicateM_ n input >> forever (input >>= output)

add :: Coroutine r Int Int ()
add = forever $ input >>= \v1 -> input >>= \v2 -> output $ v1 + v2

duplicate :: Coroutine r v v ()
duplicate = forever $ input >>= \v -> output v >> output v

-- Programs
-- 1. A program which outputs the first 5 even numbers of a stream.
-- 2. A program which produces a stream of the triangle numbers
-- 3. A program which multiplies a stream by 2
-- 4. A program which sums adjacent pairs of integers

p1, p2, p3, p4 :: Coroutine r Int Int ()

p1 = filterC even >>> limit 5
p2 = produce [ x * (x + 1) `div` 2 | x <- [1 ..] ]
p3 = duplicate >>> add
p4 = duplicate >>> suppress 1 >>> add

