{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE UndecidableInstances #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FunctionalDependencies #-}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE TypeFamilies #-}

module PolyvariadicFunctions where

class PolyAdd a where
  -- | `polyAdd` sums its arguments, all `Int`s.
  polyAdd' :: Integer -> a
--

instance (PolyAdd f, Integral n) => PolyAdd (n -> f) where
  polyAdd' a = polyAdd' . (a +) . toInteger
--

instance PolyAdd Integer where
  polyAdd' = id
--

instance PolyAdd Int where
  polyAdd' = fromInteger
--

polyAdd :: PolyAdd a => a
polyAdd = polyAdd' 0

class PolyList a r | r -> a where
  polyList' :: [a] -> r
--

a ->> b = b ++ [a]

instance (a ~ b, PolyList a r) => PolyList a (b -> r) where
  polyList' l = polyList' . (l ++) . return
--

instance PolyList a [a] where
  polyList' = id
--

polyList :: PolyList a b => b
polyList = polyList' []

class PolyWord a where
  -- | `polyWords` turns its arguments into a spaced string.
  polyWords' :: String -> a
--

instance PolyWord String where
  polyWords' [] = []
  polyWords' ls = tail ls
--

instance PolyWord f => PolyWord (String -> f) where
  polyWords' a = polyWords' . ((a ++ " ") ++)
--

polyWords :: PolyWord a => a
polyWords = polyWords' []
