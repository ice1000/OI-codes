module Postfix where

begin = ($ [])
push xs n f = f $ n : xs
add (x : y : xs) f = f (x + y : xs)
end = head

