module Codewars.G964.Getmiddle where

getMiddle :: String -> String
getMiddle s
  |odd l     = [s !! (div l 2)]
  |otherwise = [s !! (div l 2 - 1), s !! (div l 2)]
  where l = length s
--

