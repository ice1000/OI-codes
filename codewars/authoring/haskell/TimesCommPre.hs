{-# LANGUAGE TypeOperators, TypeFamilies, GADTs, UndecidableInstances, TemplateHaskell #-}

module Kata.TimesComm.Definitions where

import Control.Monad
import Language.Haskell.TH
import Test.Hspec

-- | The natural numbers, encoded in types.
data Z
data S n

-- | Predicate describing natural numbers.
-- | This allows us to reason with `Nat`s.
data Natural :: * -> * where
  NumZ :: Natural Z
  NumS :: Natural n -> Natural (S n)

instance Eq (Natural a) where
  NumZ == NumZ = True
  NumS n == NumS m = n == m
  _ == _ = False

instance Show (Natural a) where
  show NumZ = "Z"
  show (NumS n) = "S " ++ show n

-- | Predicate describing equality of natural numbers.
data Equal :: * -> * -> * where
  EqlZ :: Equal Z Z
  EqlS :: Equal n m -> Equal (S n) (S m)

instance Eq (Equal a b) where
  EqlZ == EqlZ = True
  EqlS n == EqlS m = n == m
  _ == _ = False

instance Show (Equal a b) where
  show EqlZ = "(Z==Z)"
  show (EqlS n) = "S " ++ show n

-- | Peano definition of addition.
type family (:+:) (n :: *) (m :: *) :: *
type instance Z :+: m = m
type instance S n :+: m = S (n :+: m)

-- | Peano definition of multiplication.
type family (:*:) (n :: *) (m :: *) :: *
type instance Z :*: m = Z
type instance S n :*: m = m :+: (n :*: m)

proof :: Int -> Q Exp
proof 0 = [| EqlZ |]
proof n = do
  nums <- [| EqlS |]
  rest <- proof (n-1)
  return (AppE nums rest)

nat :: Int -> Q Exp
nat 0 = [| NumZ |]
nat n = do
  nums <- [| NumS |]
  rest <- nat (n-1)
  return (AppE nums rest)

makeTests :: Q Exp -> Q Exp
makeTests a = runIO (putStrLn "Generating tests...") *> makeTests' a

makeTests' :: Q Exp -> Q Exp
makeTests' solution = DoE . map NoBindS . concat <$> do
  equals <- [| shouldBe |]
  theproof <- solution
  forM [2..4 :: Int] $ \i ->
    forM [4..6 :: Int] $ \j -> do
      ni <- nat i
      nj <- nat j
      nij <- proof (i*j)
      return (equals `AppE`
        (theproof `AppE` ni `AppE` nj) `AppE` nij)
