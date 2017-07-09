module CamelCase.JorgeVS.Kata where

import Data.List.Split
import Data.Char

camelCase :: String -> String
camelCase s = (f $ splitOn " " s) >>= id
  where f [             ] = [""]
        f ([       ] : o) = f o
        f ((h : str) : o) = (toUpper h : str) : f o
--
