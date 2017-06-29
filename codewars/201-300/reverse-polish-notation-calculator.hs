module RPN where

import Data.List.Split

eval :: [Double] -> [String] -> Double
eval [           ] [[      ]] = 0
eval (first  :  _) [        ] = first
eval (a : (b : c)) ("+" : ls) = eval ((b + a) : c) ls
eval (a : (b : c)) ("-" : ls) = eval ((b - a) : c) ls
eval (a : (b : c)) ("*" : ls) = eval ((b * a) : c) ls
eval (a : (b : c)) ("/" : ls) = eval ((b / a) : c) ls
eval stack         (num : ls) = eval ((read num :: Double) : stack) ls

calc :: String -> Double
calc = eval [] . splitOn " "
