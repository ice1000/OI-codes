{-# LANGUAGE DataKinds #-}
{-# LANGUAGE DeriveFoldable #-}
{-# LANGUAGE DeriveTraversable #-}
{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE KindSignatures #-}
{-# LANGUAGE TypeOperators #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE StandaloneDeriving #-}
{-# LANGUAGE PolyKinds #-}

module RevRevId where

import Prelude hiding (concat)
import Data.Type.Equality
import Data.Singletons

data Nat = O | S Nat deriving (Eq, Show)

data LinkedList :: * -> * where
  Nil  :: LinkedList a
  Cons :: a -> LinkedList a -> LinkedList a

data Natrual (n :: Nat) where
  Zy :: Natrual 'O
  Sy :: Natrual  n -> Natrual ('S n)

deriving instance (Show a) => Show (LinkedList a)
deriving instance Functor LinkedList
deriving instance Foldable LinkedList
deriving instance Traversable LinkedList
deriving instance Show (Natrual n)

type family (n :: Nat) :+: (m :: Nat) :: Nat
type instance 'O   :+: m =           m
type instance 'S n :+: m = 'S (n :+: m)

infixr 5 +++
(+++) :: LinkedList a -> LinkedList a -> LinkedList a
Nil +++ ls = ls
(Cons x xs) +++ ls = Cons x $ xs +++ ls

concat = (+++)

consRev :: a -> LinkedList a -> LinkedList a
consRev a Nil = Cons a Nil
consRev a n   = n +++ Cons a Nil

rev :: LinkedList a -> LinkedList a
rev  Nil = Nil
rev (Cons a n) = rev n +++ Cons a Nil

-- lemma :: (list ~ LinkedList a) => a -> list -> rev (consRev a list) :~: 'Cons a (rev list)
-- lemma a  Nil       = case (rev $ consRev a Nil, Cons a $ rev Nil) of
--   (Cons a Nil, Cons b Nil) -> Refl
-- lemma a (Cons b n) = undefined

testProof0 :: n :~: m -> 'S n :~: 'S m
testProof0 Refl = Refl
