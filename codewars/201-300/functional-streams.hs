module Stream where

import Control.Arrow
import Control.Applicative

-- import Stream.Internal

-- Defined in Stream.Internal:
data Stream a = a :> Stream a
infixr :>

-- | Get the first element of a stream.
headS :: Stream a -> a
headS (h :> t) = h

-- | Drop the first element of a stream.
tailS :: Stream a -> Stream a
tailS (h :> t) = t

-- {{{ Stream constructors

-- | Construct a stream by repeating a value.
repeatS :: a -> Stream a
repeatS a = a :> repeatS a

-- | Construct a stream by repeatedly applying a function.
iterateS :: (a -> a) -> a -> Stream a
iterateS f x = x :> (iterateS f $ f x)

-- | Construct a stream by repeating a list forever.
cycleS :: [a] -> Stream a
cycleS xs = f xs
  where f [  a  ] = a :> cycleS xs
        f (h : t) = h :> f t
--

-- | Construct a stream by counting numbers starting from a given one.
fromS :: Num a => a -> Stream a
fromS n = n :> (fromS $ n + 1)

-- | Same as 'fromS', but count with a given step width.
fromStepS :: Num a => a -> a -> Stream a
fromStepS n s = n :> (fromStepS (n + s) s)

-- }}}

-- | Fold a stream from the left.
foldrS :: (a -> b -> b) -> Stream a -> b
foldrS f (x :> xs) = f x $ foldrS f xs

-- | Filter a stream with a predicate.
filterS :: (a -> Bool) -> Stream a -> Stream a
filterS f (x :> xs) = if f x then x :> filterS f xs else filterS f xs

-- | Take a given amount of elements from a stream.
takeS :: Int -> Stream a -> [a]
takeS 0    _     = []
takeS i (h :> t)
  |i < 0     = []
  |otherwise = h : takeS (i - 1) t
    
-- | Drop a given amount of elements from a stream.
dropS :: Int -> Stream a -> Stream a
dropS 0    s     = s
dropS i s@(h :> t)
  |i < 0     = s
  |otherwise = dropS (i - 1) t

-- | Do take and drop simultaneous.
splitAtS :: Int -> Stream a -> ([a], Stream a)
splitAtS i s = (takeS i s, dropS i s)

-- | Combine two streams with a function.
zipWithS :: (a -> b -> c) -> Stream a -> Stream b -> Stream c
zipWithS f (x :> xs) (y :> ys) = f x y :> zipWithS f xs ys

zipS :: Stream a -> Stream b -> Stream (a, b)
zipS = zipWithS (,)

instance Functor Stream where
    -- fmap :: (a -> b) -> Stream a -> Stream b
    fmap f (x :> xs) = f x :> fmap f xs
--

instance Applicative Stream where
    -- pure :: a -> Stream a
    pure = repeatS
    -- (<*>) :: Stream (a -> b) -> Stream a -> Stream b
    (a :> as) <*> (b :> bs) = a b :> (as <*> bs)
--

-- | The stream of fibonacci numbers.
fibS :: Stream Integer
fibS = 0 :> 1 :> (zipWithS (+) fibS $ dropS 1 fibS)

-- | The stream of prime numbers.
primeS :: Stream Integer
primeS = sieve $ fromS 2
  where sieve (p :> xs) = p :> (sieve $ filterS (\x -> mod x p > 0) xs)
        sq = floor . sqrt . fromInteger
--
