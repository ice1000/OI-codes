module Codewars.Triangles where

import Data.List (sort)

isTriangle :: Int -> Int -> Int -> Bool
isTriangle a b c = a + b > c && b + c > a && a + c > b
