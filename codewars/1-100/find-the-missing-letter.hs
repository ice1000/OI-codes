module Kata where

findMissingLetter :: [Char] -> Char
findMissingLetter (c1 : cs@(c2 : _))
  |succ c1 == c2 = findMissingLetter cs
  |otherwise     = succ c1
--

