module Codewars.Kata.IsUpperCase where

isUpperCase :: String -> Bool
isUpperCase = not . any (`elem` ['a'..'z'])
