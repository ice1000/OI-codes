module Imperative (
  def, var, lit, while, (+=), (-=), (*=)
  ) where

data M a = M a
data V = V Integer

instance Functor M where fmap f (M a) = M $ f a

instance Applicative M where
  pure = M
  M f <*> M a = M $ f a
--

instance Monad M where
  return a    = M a
  (M a) >>= f = f a
--

def :: V -> Integer
def (V i) = i

var :: Integer -> M V
var = undefined

lit :: Integer -> V
lit = V

while :: V -> (Integer -> Bool) -> M () -> M ()
while = undefined

a += b = error "todo: (+=)"

a -= b = error "todo: (-=)"

a *= b = error "todo: (*=)"

