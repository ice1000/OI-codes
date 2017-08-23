{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE UndecidableInstances #-}

module PolyvariadicFunctions where

import Control.Arrow

class PolyAdd a where
  -- | `polyAdd` sums its arguments, all `Int`s.
  polyAdd' :: Integral i => i -> a
--

class PolyList a where
  -- | `polyList` turns its arguments into a list, polymorphically.
  polyList :: a
--

class PolyWord a where
  -- | `polyWords` turns its arguments into a spaced string.
  polyWords :: a
--

instance (PolyAdd f, Integral n) => PolyAdd (n -> f) where
  polyAdd' a = (a +) >>> polyAdd'
--

instance Integral n => PolyAdd n where
  polyAdd' = id
--

polyAdd :: PolyAdd a => a
polyAdd = polyAdd' 0
