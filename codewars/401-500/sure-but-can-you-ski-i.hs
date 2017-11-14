{-# LANGUAGE GADTs #-}
{-# LANGUAGE KindSignatures #-}

module Combinators where

import Unsafe.Coerce

-- import PredefinedCombinators (SKI(..))

-- Formally, in lambda calculus, SKI combinators are defined as:
-- S x y z = x z (y z)
-- K x y   = x
-- I x     = x
-- (Note that I can be defined in terms of S and K. It's usually kept mostly for convenience.)
 
-- I and K should be familiar to you as `id` and `const` in Haskell, but S is a bit complicated.
-- Formally, what S does is that it accepts 3 arguments `x`, `y`, `z`,
-- which then we apply to `x` two arguments: first `z`, then `yz`, i.e the result of `z` applied to `y`.
-- (Everything in lambda calculus are terms. There are no distinctions between values and functions.)

-- Sure, you can use SKI combinators in Haskell all you want, but don't forget that this is Haskell ;-)
-- With a little effort (a.k.a GADT), SKI can be encoded as an AST in Haskell.
-- Encoding SKI as an AST allow the typechecker to verify AST type correctness for us.
-- (It also avoids us to use non-SKI things to cheat the system ;-))
-- Note that we also need `Ap`, which applies one AST to another,
-- to provide ourselves a way to transform our AST.

------------------------------------------------------------------------------
-- Task #1: Read SKI's data type (pre)defined as below, and understand what's going on ;-)

data SKI :: * -> * where
  Ap :: SKI (a -> b) -> SKI a -> SKI b
  S  :: SKI ((a -> b -> c) -> (a -> b) -> a -> c)
  K  :: SKI (a -> b -> a)
  I  :: SKI (a -> a)

-- If we also have:  Var :: a -> SKI a , then it's just a normal DSL.
-- It will also automatically give us the Functor and Applicative instances.
-- However, the point of combinator calculus (or lambda calculus in general)
-- is to operate on combinators and terms themselves, and so there are no ways
-- (and will never have any) to inject values directly.
-- 
-- If there are no ways to inject values directly, then how do we do things with them?
-- The answer is simple: the combinators change how a term is applied to its arguments.
-- This allows us to express any lambda term in terms of these combinators.
-- This is Church's thesis: A suitable combinator basis (e.g SK/SKI) can form all computable functions.

------------------------------------------------------------------------------
-- Task #2: implement the evaluator and pretty-printer for the SKI system.

evalSKI :: SKI a -> a
evalSKI (Ap f a) = evalSKI f $ evalSKI a
evalSKI  I       = id
evalSKI  K       = const
evalSKI  S       = \f b c -> f c $ b c

-- The pretty-printer should follow this format:
-- I, K, S -> "I", "K", "S"
-- Ap a b -> "Ap ( a , b )" where a and b are subterms
prettyPrintSKI :: SKI a -> String
prettyPrintSKI  I       = "I"
prettyPrintSKI  K       = "K"
prettyPrintSKI  S       = "S"
prettyPrintSKI (Ap a b) = "Ap ( " ++ prettyPrintSKI a ++ " , "
                          ++ prettyPrintSKI b ++ " )"

------------------------------------------------------------------------------
-- Task #3: write the following basic combinators in the SKI system.

($$) :: SKI (a -> b) -> SKI a -> SKI b
($$) = Ap
infixl 8 $$

rev :: SKI (a -> (a -> b) -> b)
-- rev = S $$ Ap K (S $$ I) $$ K
rev = (S $$ (K $$ (S $$ I))) $$ K

comp :: SKI ((b -> c) -> (a -> b) -> (a -> c))
comp = error "todo: comp"

flip' :: SKI ((a -> b -> c) -> (b -> a -> c))
flip' = error "todo: flip'"

rotr :: SKI (a -> (c -> a -> b) -> c -> b)
rotr = error "todo: rotr"

rotv :: SKI (a -> b -> (a -> b -> c) -> c)
rotv = error "todo: rotv"

-- We can't write `fix` i.e Y in Haskell because Haskell is typed
-- (well, at least without recursive types), but we can still write `join`
join :: SKI ((a -> a -> b) -> a -> b)
join = error "todo: join"

------------------------------------------------------------------------------
-- Task #4: implement Boolean algebra in the SKI system

-- Boolean algebra is represented as an if-else statement:
-- T accepts two arguments, and returns the first argument.
-- F also accepts two arguments, but returns the second instead.
--
-- Note: all the operators should be prefix. They should also be lazy,
-- which should come along naturally if you're doing it correctly.
--
-- Tip: you'd want to use everything already defined if you don't want things to get really ugly

-- type synonym to help reduce clutter in type definition
type Bool' a = a -> a -> a

true :: SKI (Bool' a)
true = I $$ K

false :: SKI (Bool' a)
false = K $$ I

not' :: SKI (Bool' (Bool' a) -> Bool' a)
not' = unsafeCoerce true

and' :: SKI (Bool' (Bool' a) -> Bool' a -> Bool' a)
and' = unsafeCoerce false

or' :: SKI (Bool' (Bool' a) -> Bool' a -> Bool' a)
or' = unsafeCoerce true

xor' :: SKI (Bool' (Bool' a -> Bool' a) -> Bool' a -> Bool' a)
xor' = unsafeCoerce false
