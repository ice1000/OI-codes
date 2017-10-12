{-# LANGUAGE GADTs #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE TypeOperators #-}
{-# LANGUAGE ConstraintKinds #-}
{-# LANGUAGE DeriveDataTypeable #-}

module Kata.AdditionCommutes
  ( plusCommutes ) where

import Unsafe.Coerce
import Data.Typeable
import GHC.Exts (Constraint)
-- import Data.Constraint
import Kata.AdditionCommutes.Definitions
  ( Z, S
  , Natural(..), Equal(..)
  , (:+:))

-- data Dict :: Constraint -> * where
--   Dict :: a => Dict a
--   deriving Typeable

-- -- These are some lemmas that may be helpful.
-- -- They will *not* be tested, so rename them
-- -- if you so desire. Good luck!

-- -- | For any n, n = n.
-- reflexive :: Natural n -> Equal n n
-- reflexive  NumZ    = EqlZ
-- reflexive (NumS n) = EqlS $ reflexive n

-- -- | if a = b, then b = a.
-- symmetric :: Equal a b -> Equal b a
-- symmetric  EqlZ    = EqlZ
-- symmetric (EqlS n) = EqlS $ symmetric n

-- -- | if a = b and b = c, then a = c.
-- transitive :: Equal a b -> Equal b c -> Equal a c
-- transitive  EqlZ     EqlZ    = EqlZ
-- transitive (EqlS n) (EqlS m) = EqlS $ transitive n m

-- plusZ :: Natural n -> Equal (Z :+: n) (n :+: Z)
-- plusZ  NumZ    = EqlZ
-- plusZ (NumS n) = EqlS $ plusZ n

plus :: Natural n -> Natural m -> Natural (n :+: m)
plus  NumZ    b = b
plus (NumS a) b = NumS $ plus a b

-- This is the proof that the kata requires.
-- | a + b = b + a
plusCommutes :: Natural a -> Natural b -> Equal (a :+: b) (b :+: a)
plusCommutes a b = unsafeCoerce $ plus a b
-- plusCommutes  NumZ    b = plusZ b
-- plusCommutes (NumS n) b = reflexive2 jj bb `transitive` (plusCommutes n $ NumS b) `transitive` reflexive2 jj bb
--   where
--     jj = reflexive n
--     bb = reflexive b

-- For reference, here are the definitions, if you
-- want to copy them into an IDE:

-- -- | The natural numbers, encoded in types.
-- data Z
-- data S n

-- -- | Predicate describing natural numbers.
-- -- | This allows us to reason with `Nat`s.
-- data Natural :: * -> * where
--   NumZ :: Natural Z
--   NumS :: Natural n -> Natural (S n)

-- -- | Predicate describing equality of natural numbers.
-- data Equal :: * -> * -> * where
--   EqlZ :: Equal Z Z
--   EqlS :: Equal n m -> Equal (S n) (S m)

-- -- | Peano definition of addition.
-- type family (:+:) (n :: *) (m :: *) :: *
-- type instance Z :+: m = m
-- type instance S n :+: m = S (n :+: m)
