module Codewars.BackspacesInString where

cleanString :: String -> String
cleanString [] = []
cleanString ls = reverse $ foldl f [] ls
  where f [     ] '#' = []
        f (a : b) '#' = b
        f theList  c  = c : theList
--

